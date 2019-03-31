# MVC

## Java Spring

```txt
- dto
- controller
```

![DTO BO MO DAL](./asset/dto-bo-mo-dal.png)

* **Entity**
* **DTO** is an object that carries data between processes. When you're working with a remote interface, each call it is expensive. As a result you need to reduce the number of calls. The solution is to create a Data Transfer Object that can hold all the data for the call. It needs to be serializable to go across the connection. Usually an assembler is used on the server side to transfer data between the DTO and any domain objects. It's often little more than a bunch of fields and the getters and setters for them.
* **DAO** A Data Access Object abstracts and encapsulates all access to the data source. The DAO manages the connection with the data source to obtain and store data. The DAO implements the access mechanism required to work with the data source. The data source could be a persistent store like an RDBMS, or a business service accessed via REST or SOAP. The DAO abstracts the underlying data access implementation for the Service objects to enable transparent access to the data source. The Service also delegates data load and store operations to the DAO. 主要用来封装对数据库的访问。通过它可以把POJO持久化为PO，用PO组装出来VO、DTO
* **BO** 主要作用是把业务逻辑封装为一个对象。这个对象可以包括一个或多个其它的对象。比如一个简历，有教育经历、工作经历、社会 关系等等。我们可以把教育经历对应一个PO，工作经历对应一个PO，社会 关系对应一个PO。建立一个对应简历的BO对象处理简历，每个BO包含这些PO。这样处理业务逻辑时，我们就可以针对BO去处理。
* **Service** Service objects are doing the work that the application needs to do for the domain you're working with. It involves calculations based on inputs and stored data, validation of any data that comes in from the presentation, and figuring out exactly what data source logic to dispatch, depending on commands received from the presentation. A Service Layer defines an application's boundary and its set of available operations from the perspective of interfacing client layers. It encapsulates the application's business logic, controlling transactions and coordinating responses in the implementation of its operations.
* **Biz** bussiness layer
* **PO** Persistent object. A record of the image understanding is a PO that is in the database. The benefits can be put a record as an object, it will be convenient to the other objects.
