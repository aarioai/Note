# Tree Travesals
https://en.wikipedia.org/wiki/Tree_traversal
```
                        (F1)
                      /      \
                    (B2)      (G3)
                   /    \        \
                 (A4)   (D5)     (I6)
                        /  \      /
                      (C7)(E8)  (H9)

Pre-order Tranversal(NLR):   Node --> Left --> Right
    F1 -> B2 -> A4 -> D5 -> C7 -> E8
                                     -> G3 -> I6 -> H9

In-order Tranversal(LNR):    Left -> Node -> Right
    A4 -> B2 -> C7 -> D5 -> E8
                               -> F1
                                     -> G3 -> H9 -> I6

Post-order Transversal(LRN): Left -> Right -> Node
    A4 -> C7 -> E8 -> D5 -> B2
                               -> H9 -> I6 -> G3
                                                 -> F1

Level-order Traversal(Breadth first):
    F -> B -> G
                -> A -> D
                          -> I
                               -> C -> E
                                         -> H
```
## Use Queue to solve level-order traversal
```
Queue(FIFO)
    F1 --> enqueue(B2, G3)                  Q[G3, B2]
        dequeue B2                          Q[G3]
    B2 --> enqueue(A4, D5)                  Q[D5, A5, G3]
    while Q is not empty
        enqueue children
        dequeue the leftmost element
```
