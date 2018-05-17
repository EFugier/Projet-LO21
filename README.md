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
   'nbNeighboor': 5,
   'default': -1,  // -1: last satate, 1: 0: dead, 1: alive
   'softPositions': [
       [[0, 1], [1, 0], [5, 1]],
       [[0, 0]]
   ],
   'absolutePositions': [
       [0, 1, 1, 0, 0],
       [0, 1, 0, 0, 0],
       [0, 0, 0, 1],
       [1, 1, 1, 1]
   ],
   'positionTree': [...]  // To be calculated
   'death': [[0,2],[5,6]],
   'birth': [[3,4]]
}
```
