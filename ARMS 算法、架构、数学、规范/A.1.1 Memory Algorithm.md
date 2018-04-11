# Least Recently Used
buffer size: 3   [?|?|?]
data:  4 3 4 5 1 3 5 ...

datum: 4 --> [4|?|?]
datum: 3 --> [3|4|?]
datum: 4 --> [4|3|?]
datum: 5 --> [5|4|3]
datum: 1 --> [1|5|4]
... 
