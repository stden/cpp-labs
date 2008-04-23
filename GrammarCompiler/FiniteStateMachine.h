//
// File:    FSM.h
// 
// Date:    23 January 2003
//
// Purpose: Finite State Machine template
// 
// Copyright (c) Serguei Satski 2003
//
// Permission to copy, use, modify, sell and distribute this software 
// is granted provided this copyright notice appears in all copies. 
// This software is provided "as is" without express or implied
// warranty, and with no claim as to its suitability for any purpose.
//

#ifndef _FSMTEMPLATE_
#define _FSMTEMPLATE_

#include <vector>
#include <algorithm>
#include <stdexcept>
#include <deque>
#include <string>
#include <functional>
#include <iterator>
#include <iostream>

#define FSMBEGIN( StartFSMState )  (StartFSMState), \
                                   (FSM::SFiniteStateMachineProxy<FSMStateType,FSMEventType>())<<(FSM::SStatesListProxy<FSMStateType>() <<
#define FSMSTATES
#define FSMEVENT( Arg )            ) \
                                   << ( (FSM::STransitionsProxy<FSMStateType,FSMEventType>)( Arg ) <<
#define FSMEND                     )
#define FSMRESET                   FSM::ResetMachine


namespace FSM
{
    enum SMachineManipulator { ResetMachine = 0 };
    
        //
        // Exception definition for the state machine template class
        //
    class SStateMachineException : public std::exception
    {
        private:
            const std::string      Message;

        public:
            SStateMachineException( const std::string &  Msg ) : Message( Msg ) {}
            SStateMachineException( const char *         Msg ) : Message( Msg ) {}

            virtual const char * what( void ) const throw() { return Message.c_str(); }
            virtual ~SStateMachineException() throw () {}

        private:
            SStateMachineException();
    };


        //
        // No entry, no exit functions calls strategy
        //
    template <class SState, class SEvent>
    class SEmptyFunctor
    {
        public:
            inline void operator() ( SState &  From, const SEvent &  Event, SState &  To ) { return; }
    };

        //
        // Entry functions calls strategy
        //
    template <class SState, class SEvent>
    class SOnEnterFunctor
    {
        public:
            inline void operator() ( SState &  From, const SEvent &  Event, SState &  To )
            { To.OnEnter( From, Event ); }
    };

        //
        // Exit functions calls strategy
        //
    template <class SState, class SEvent>
    class SOnExitFunctor
    {
        public:
            inline void operator() ( SState &  From, const SEvent &  Event, SState &  To )
            { From.OnExit( Event, To ); }
    };

        //
        // Both entry and exit functions calls strategy
        //
    template <class SState, class SEvent>
    class SOnMoveFunctor
    {
        public:
            inline void operator() ( SState &  From, const SEvent &  Event, SState &  To )
            { From.OnExit( Event, To ); To.OnEnter( From, Event ); }
    };
        
        //
        // Throw exception strategy for the unknown event
        //
    template <class SEvent>
    class SThrowStrategy
    {
        public:
            inline void operator() ( const SEvent & ) const { throw SStateMachineException( "Unknown event." ); }
    };

        //
        // Ignore strategy for the unknown event
        //
    template <class SEvent>
    class SIgnoreStrategy
    {
        public:
            inline void operator() ( const SEvent & ) const { return; }
    };

        //
        // Temporary class to collect all the registered states
        //
    template <class SState>
    class SStatesListProxy
    {
        private:
            std::vector<SState>    StatesProxy;

        public:
            SStatesListProxy() { return; }
            SStatesListProxy &  operator << ( const SState &  TheState )
            { 
                    // Check whether the state is unique
                if ( std::find( StatesProxy.begin(), StatesProxy.end(), TheState ) != StatesProxy.end() ) 
                    throw SStateMachineException( "States must be unique." );
                StatesProxy.push_back( TheState ); 
                return *this; 
            }
            inline const std::vector<SState> &  GetStates( void ) const { return StatesProxy; }
    };

    
        //
        // Temporary class to collect transitions for a single event
        //
    template <class SState, class SEvent>
    class STransitionsProxy
    {
        private:
            SEvent                      Event;
            std::vector<SState>         NewStates;

        public:
            explicit STransitionsProxy( const SEvent &  TheEvent ) : Event( TheEvent ) { return; }
            STransitionsProxy & operator << ( const SState &  TheState ) { NewStates.push_back( TheState ); return *this; }
            inline const std::vector<SState> &  GetStates( void ) const { return NewStates; }
            inline const SEvent &  GetEvent( void ) const { return Event; }

        private:
            STransitionsProxy();
    };

        //
        // Temporary class to collect all the transitions
        //
    template <class SState, class SEvent>
    class SFiniteStateMachineProxy
    {
        private:
            std::vector<SState>                     MachineStatesProxy;
            bool                                    HaveStates;
            std::vector<SEvent>                     MachineEventsProxy;
            std::vector< std::vector<SState> >      Transitions;
    
        public:
            SFiniteStateMachineProxy() : HaveStates( false ) { return; }
            SFiniteStateMachineProxy & operator << ( const SStatesListProxy<SState> &   TheStates ) 
            { 
                if ( HaveStates ) throw SStateMachineException( "Too much state lists." );
                HaveStates = true;
                MachineStatesProxy = TheStates.GetStates();
                return *this; 
            }
            SFiniteStateMachineProxy & operator << ( const STransitionsProxy<SState,SEvent> &  TheTransitions ) 
            { 
                if ( !HaveStates ) throw SStateMachineException( "States must be defined before the transitions." );
            
                if ( MachineStatesProxy.size() != TheTransitions.GetStates().size() ) 
                    throw SStateMachineException( "Transition states do not coincide to the states list." );

                    // Check that the event is unique
                if ( std::find( MachineEventsProxy.begin(), MachineEventsProxy.end(), TheTransitions.GetEvent() ) != MachineEventsProxy.end() ) 
                    throw SStateMachineException( "Events must be unique." );
                    
                    // Check the transition validity
                CheckTransitionValidity( TheTransitions.GetStates().begin(), TheTransitions.GetStates().end() );

                MachineEventsProxy.push_back( TheTransitions.GetEvent() );
                Transitions.push_back( TheTransitions.GetStates() );
                return *this; 
            }
                
                
                //
                // Check that the transitions lead to a registered state
                //
            inline void CheckTransitionValidity( typename std::vector<SState>::const_iterator First, typename std::vector<SState>::const_iterator  Last )
            {
                for ( ; First != Last; ++First )
                {
                    if ( std::find( MachineStatesProxy.begin(), MachineStatesProxy.end(), *First ) == MachineStatesProxy.end() ) 
                        throw SStateMachineException( "Transition state is not valid." );
                }
            }       

            inline const std::vector<SState> &  GetStates( void ) const                    { return MachineStatesProxy; }
            inline const std::vector< std::vector<SState> > & GetTransitions( void ) const { return Transitions;        }
            inline const std::vector<SEvent> &  GetEvents( void ) const                    { return MachineEventsProxy; }
    };

            
        //
        // Finite state machine template
        //
    template <class SState, class SEvent, class SFunctor = SEmptyFunctor<SState,SEvent>, class SUnknownEventStrategy = SThrowStrategy<SEvent> > 
    class SFiniteStateMachine
    {
        public:
            typedef SState     StateType;
            typedef SEvent     EventType;

        private:
            StateType                               CurrentState;               // Current machine state
            std::vector<StateType>                  States;                     // A list of the registered states
            std::vector<EventType>                  Events;                     // A list of the registered events
            std::vector< std::vector<StateType> >   Transitions;                // A table of transitions between states
            SFunctor                                Functor;                    // Transition function
            SUnknownEventStrategy                   UnknownEventStrategy;       // Unknown event strategy
            std::deque<EventType>                   EventsQueue;                // Internal events queue to support events 
                                                                                //   that were generated in the transition functions
            bool                                    InProcess;                  // To be sure that we are in the process of events
            int                                     CurrentStateIndex;          // Index of column in a transition table (0 - based)
            StateType                               InitialState;               // Start machine state

        public:
            SFiniteStateMachine( const StateType &  StartState, const SFiniteStateMachineProxy<StateType,EventType> &  ProxyMachine ) :
                CurrentState( StartState ), States( ProxyMachine.GetStates() ),
                Events( ProxyMachine.GetEvents() ), Transitions( ProxyMachine.GetTransitions() ), InProcess( false ),
                CurrentStateIndex( -1 ), InitialState( StartState )
            {
                    // Check that the start state is valid
                typename std::vector<StateType>::iterator  k( std::find( States.begin(), States.end(), StartState ) );
                if ( k == States.end() ) throw SStateMachineException( "Start state is not valid." );
                CurrentStateIndex = std::distance( States.begin(), k );
            }

                //
                // Reset the machine to the initial state.
                // Warning: no transition functions will be called if any
                //
            inline SFiniteStateMachine & Reset( void ) 
            {
                CurrentState = InitialState; 
                CurrentStateIndex = GetStateIndex( CurrentState );
                InProcess = false;
                EventsQueue.clear();
                return *this;
            }

                //
                // Returns the current machine state
                //
            inline StateType GetCurrentState( void ) const { return CurrentState; }

                //
                // Accepts an event
                //
            SFiniteStateMachine &  AcceptEvent( const EventType &  Event )
            {
                EventsQueue.push_back( Event );
                if ( InProcess ) return *this;
                InProcess = true;
                while ( !EventsQueue.empty() )
                {   ProcessEvent( EventsQueue.front() );
                    EventsQueue.pop_front();
                }
                InProcess = false;
                return *this;
            }

            inline SFiniteStateMachine & operator << ( const EventType &  Event )        { return AcceptEvent( Event ); }
            inline SFiniteStateMachine & operator << ( SMachineManipulator Manipulator ) { if ( Manipulator == ResetMachine ) return Reset(); return *this; } 
        
        private:
            inline void ProcessEvent( const EventType &  Event )
            {   
                int  EventIndex( GetEventIndex( Event ) );
                if ( EventIndex == -1 ) return;

                StateType      OldState( CurrentState );
            
                CurrentState = (Transitions[EventIndex])[CurrentStateIndex];
                CurrentStateIndex = GetStateIndex( CurrentState );

                Functor( OldState, Event, CurrentState );
            }
        
            inline int GetEventIndex( const EventType &  Event ) const
            {   
                typename std::vector<EventType>::const_iterator   k( std::find( Events.begin(), Events.end(), Event ) );
                if ( k == Events.end() ) { UnknownEventStrategy( Event ); return -1; }
                return std::distance( Events.begin(), k );
            }

            inline int GetStateIndex( const StateType &  State ) const
            {
                return std::distance( States.begin(), std::find( States.begin(), States.end(), State ) );
            }

        private:
                //
                // Prevent the illegal usage
                //
            SFiniteStateMachine();
            SFiniteStateMachine & operator= ( const SFiniteStateMachine & );
            SFiniteStateMachine( const SFiniteStateMachine & );
    };
    
        //
        // Allow writing the current machine state to an output stream 
        //
    template <class SState, class SEvent, class SFunctor, class SUnknownEventStrategy > 
        std::ostream & operator << (std::ostream &  Stream, const SFiniteStateMachine<SState,SEvent,SFunctor,SUnknownEventStrategy> &  Machine )
    { return Stream << Machine.GetCurrentState(); }
    
}   // End of the FSM namespace

#endif

