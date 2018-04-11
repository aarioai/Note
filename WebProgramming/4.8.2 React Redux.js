/**
 * @see https://github.com/reactjs/redux
 * @see https://github.com/happypoulp/redux-tutorial

                 _________               ____________               ___________
                |         |             |            |             |           |
                | Action  |------------▶| Dispatcher |------------▶| callbacks |
                |_________|             |____________|             |___________|
                     ▲                                                   |
                     |                                                   |
                     |                                                   |
 _________       ____|_____                                          ____▼____
|         |◀----|  Action  |                                        |         |
| Web API |     | Creators |                                        |  Store  |
|_________|----▶|__________|                                        |_________|
                     ▲                                                   |
                     |                                                   |
                 ____|________           ____________                ____▼____
                |   User       |         |   React   |              | Change  |
                | interactions |◀--------|   Views   |◀-------------| events  |
                |______________|         |___________|              |_________|
                
Let's pretend we're building a web application. What are all web applications made of?
1) Templates / html = View
2) Data that will populate our views = Models
3) Logic to retrieve data, glue all views together and to react accordingly to user events,
   data modifications, etc. = Controller

This is the very classic MVC that we all know about. But it actually looks like concepts of flux,
just expressed in a slightly different way:
- Models look like stores
- user events, data modifications and their handlers look like
  "action creators" -> action -> dispatcher -> callback
- Views look like React views (or anything else as far as flux is concerned)            
 */