## Mini Database Management System

This is a university project on which my college and I work together. Currently it is under development. 
The main concept is that we need to write a mini database management system that creates databases, tables, fields. 
Then we implemented the basic dbms functionalities: drop,insert values, delete.  
The project still in progress in the next section we will write the join and select functions/gui. 
The backend part is connected with the MongoDB for easier data retrieval (we do not have to implement B+ trees just use the built in functions), but the indexing and any built-in thing needed to be implemented by us.

## Usage
* Main menu
<img src="https://i.imgur.com/LYObyQ5.jpg" width="650">

* Create Database - Creates the database (in the same time a MongoDB collection)
<img src="https://i.imgur.com/LYObyQ5.jpg" width="650">

* Create Tables - In the menu above are the databases which are stored locally and in MongoDB too
<img src="https://i.imgur.com/UlQlBkp.jpg" width="650">

* Modify: For creating/dropping db-s tables, insert field values, making the indexed files and link tables with foreign keys
<img src="https://i.imgur.com/peBX8CN.jpg" width="650">

* Inserting field values - the inserting is linked with mongo collections, so before inserting the backend on server_wip always check the unique,fk,duplicated data restriction
<img src="https://i.imgur.com/LpxzhKI.jpg" width="650">

* Deleting field values - it's the same restriction checking as in the inserting, the datas will be removed in MongoDB too.
<img src="https://i.imgur.com/bQbrSJ8.jpg" width="650">
