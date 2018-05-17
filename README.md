Projet-LO21
===

# Guidelines
* Full English
* Full camelCase

# UML
![](uml.png)

# Files
## Automata
``` json
{
   "nbNeighboor": 5,
   "default": 2,
   "absolutePositions": [
       "1:0,1,1,0,0",
       [0, 1, 0, 0, 0],
       [1, 0, 0, 1, 0],
       [1, 1, 1, 1, 0]
   ],
   "softPositions": [
       "1:0,1,5-1,0,1",
       [0, 1, 5], [1, 0, 1]],
       [0, [0], [0]]
   ],
   "positionTree": ['r', -1, 0, 1, -1, 0, 0, 0, -2, 1, 0, 0, -2, 1, -1, 0, 0, 1, 0, -2, 1, 1, 1, 0, -2],
   "death": [[0,2],[5,6]],
   "birth": [[3,4]]
}
```
### Parameters
* *nbNeighboor*: number of neighboors considering for state transitionning.
* *default*: default value to transition to when the current state is not handled by the other porperties.
   * 0: dead
   * 1: alive
   * 2: same
* *absolutePositions*: particular cases.
* *softPositions*: association list `[s, [i1, i2], [v1, v2]]`, transition the cell value to `s` when slot `i` has value `v`. (soft beacause constraints are softs)
