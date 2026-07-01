# Finite State Machine (FSM) Vending Machine Controller

## Algorithmic State Transition Diagram
```text
  ┌─────────────────────────────────[ CANCEL ]──────────────────────────────┐
  │                                                                         │
  ▼                                                                         │
[ STATE_IDLE ] ──► [ COIN_INSERTED ] ──► [ ITEM_SELECTED ] ──► [ STATE_DISPENSING ]
       ▲                                                                    │
       └─────────────────────────────[ CYCLE COMPLETE ]─────────────────────┘