#include "Simulator.h"
#include "Errors.h"

namespace iron
{
namespace core
{

bool Simulator::checkUUID(UUID lookup) const
{
    return !m_substates.count(lookup);
}

ErrorCode Simulator::addComponent(const std::string& behavior, UUID lookup)
{
    if(m_substates.count(lookup))
    {
        //report error
        return ErrorCode::UuidTaken;
    }

    decltype(m_types)::iterator biter = m_types.find(behavior);
    if(biter == m_types.end())
    {
        //report error
        return ErrorCode::BehaviorNotFound;
    }
    
    State inserted;
    inserted.behavior = &biter->second;
    inserted.inputs.resize(inserted.behavior->inputSizes.size());
    inserted.outputs.resize(inserted.behavior->outputSizes.size());
    for(int i = 0; i < inserted.outputs.size(); i++)
        inserted.outputs[i].value.data.resize(inserted.behavior->outputSizes[i]);
    inserted.state.resize(inserted.behavior->internalSizes.size());
    for(int i = 0; i < inserted.state.size(); i++)
        inserted.state[i].data.resize(inserted.behavior->internalSizes[i]);

    m_substates.insert(std::make_pair(lookup, std::move(inserted)));

    return ErrorCode::NoError;
}

ErrorCode Simulator::removeComponent(UUID lookup)
{
    decltype(m_substates)::iterator iter = m_substates.find(lookup);
    if(iter == m_substates.end())
    {
        //report error
        return ErrorCode::NotFound;
    }

    m_substates.erase(iter);

    return ErrorCode::NoError;
}

ErrorCode Simulator::touch(UUID lookup)
{
    decltype(m_substates)::iterator iter = m_substates.find(lookup);
    if(iter == m_substates.end())
    {
        //report error
        return ErrorCode::NotFound;
    }
    m_pushJob(lookup, 0);
    return ErrorCode::NoError;
}

ErrorCode Simulator::modifyInternal(UUID lookup, int index, const Signal& value)
{
    ErrorCode retval = modifyInternalQuiet(lookup, index, value);
    if(retval == ErrorCode::NoError)
        retval = touch(lookup);
    return retval;
}

ErrorCode Simulator::modifyInternalQuiet(UUID lookup, int index, const Signal& value)
{
    decltype(m_substates)::iterator iter = m_substates.find(lookup);
    if(iter == m_substates.end())
    {
        //report error
        return ErrorCode::NotFound;
    }
    else if(index < 0)
    {
        //report error
        return ErrorCode::NegativeIndex;
    }
    else if(index > iter->second.state.size())
    {
        //report error
        return ErrorCode::IndexExcedesBounds;
    }
    else if(value.size() != iter->second.state[index].size())
    {
        //report error
        return ErrorCode::SignalDimensionMismatch;
    }
    iter->second.state[index] = value;
    return ErrorCode::NoError;
}

std::pair<const Signal&, ErrorCode> Simulator::peekInternal(UUID lookup, int index) const
{
    decltype(m_substates)::const_iterator iter = m_substates.find(lookup);
    if(iter == m_substates.end())
    {
        //report error
        return std::make_pair(m_defaultReturn, ErrorCode::NotFound);
    }
    else if(index < 0)
    {
        //report error
        return std::make_pair(m_defaultReturn, ErrorCode::NegativeIndex);
    }
    else if(index > iter->second.state.size())
    {
        //report error
        return std::make_pair(m_defaultReturn, ErrorCode::IndexExcedesBounds);
    }

    return std::make_pair(iter->second.state[index], ErrorCode::NoError);
}

std::pair<const Signal&, ErrorCode> Simulator::peekOutput(UUID lookup, short index) const
{
    decltype(m_substates)::const_iterator iter = m_substates.find(lookup);
    if(iter == m_substates.end())
    {
        //report error
        return std::make_pair(m_defaultReturn, ErrorCode::NotFound);
    }
    else if(index < 0)
    {
        //report error
        return std::make_pair(m_defaultReturn, ErrorCode::NegativeIndex);
    }
    else if(index > iter->second.outputs.size())
    {
        //report error
        return std::make_pair(m_defaultReturn, ErrorCode::IndexExcedesBounds);
    }

    return std::make_pair(iter->second.state[index], ErrorCode::NoError);
}

std::pair<const Signal&, ErrorCode> Simulator::peekOutput(Pin output) const
{
    return peekOutput(output.uuid, output.index);
}

std::pair<const Signal&, ErrorCode> Simulator::peekInput(UUID lookup, short index) const
{
    decltype(m_substates)::const_iterator iter = m_substates.find(lookup);
    if(iter == m_substates.end())
    {
        //report error
        return std::make_pair(m_defaultReturn, ErrorCode::NotFound);
    }
    else if(index < 0)
    {
        //report error
        return std::make_pair(m_defaultReturn, ErrorCode::NegativeIndex);
    }
    else if(index > iter->second.inputs.size())
    {
        //report error
        return std::make_pair(m_defaultReturn, ErrorCode::IndexExcedesBounds);
    }
    
    return peekOutput(iter->second.inputs[index]);//Doing this may make error reporting more complex, but follows DRY
}

std::pair<const Signal&, ErrorCode> Simulator::peekInput(Pin input) const
{
    return peekInput(input.uuid, input.index);
}

ErrorCode Simulator::addConnection(Pin source, Pin destination)
{

}

ErrorCode Simulator::addConnection(const Connection& connect)
{
    return addConnection(connect.source, connect.destination);
}

ErrorCode Simulator::removeConnection(Pin source, Pin destination)
{

}

ErrorCode Simulator::removeConnection(const Connection& connect)
{
    return removeConnection(connect.source, connect.destination);
}

ErrorCode Simulator::moveConnection(Pin source, Pin destination, Pin newSoucre, Pin newDestination)
{

}

ErrorCode Simulator::moveConnection(const Connection& connect, const Connection& newConnect)
{
    return moveConnection(connect.source, connect.destination, newConnect.source, newConnect.destination);
}

ErrorCode Simulator::moveConnectionSource(Pin source, Pin destination, Pin newSource)
{

}

ErrorCode Simulator::moveConnectionSource(const Connection& connect, Pin newSource)
{
    return moveConnectionSource(connect.source, connect.destination, newSource);
}

ErrorCode Simulator::moveConnectionDestination(Pin source, Pin destination, Pin newDestination)
{

}

ErrorCode Simulator::moveConnectionDestination(const Connection& connect, Pin newDestination)
{
    return moveConnectionDestination(connect.source, connect.destination, newDestination);
}

//=====Implementation methods=====

void Simulator::m_pushJob(UUID job, int when)
{
    m_filling.insert(job);
}

bool Simulator::m_topJob(UUID& job)
{
    if(m_emptying.empty())
        return false;
    job = *m_emptying.begin();
    return true;
}

bool Simulator::m_popJob(UUID& job)
{
    if(m_emptying.empty())
        return false;
    job = *m_emptying.begin();
    m_emptying.erase(m_emptying.begin());
    return true;
}

}
}