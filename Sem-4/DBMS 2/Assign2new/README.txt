We have a C++ program populate_into_db.cpp that does the following when executed:
   * Creates a db with the name 'research_papers_db'
   * Creates a database schema as described in the schema file
   * Parses the source.txt file
   * Inserts all the data 

Make sure that libpqxx and C++ boost libraries are installed on your system.
   (Note that boost library is used only to use a trim() function for data cleaning)
   * sudo apt install libpqxx-dev
   * sudo apt-get install libboost-all-dev

Instructions to compile and run this program
   * g++ populate_into_db.cpp -o pop -lpqxx
   * ./pop
    Remember to copy source.txt into the folder where this file is located.
	Also set your postgress password into the variable myPASSWORD on line 34.

If you want to measure time taken to run this program,
   * time ./pop
   The 'real' time is the time taken by the program