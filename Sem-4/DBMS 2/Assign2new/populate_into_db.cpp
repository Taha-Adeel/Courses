/**
 * @file populate_into_db.cpp
 * @author Team 42 (Gautham Bellamkonda, Taha Adeel Mohammad, Shambu Kavir, Prateek)
 * @brief This is a C++ program that does the following when executed:
   * Creates a db with the name 'research_papers_db'
   * Creates a database schema as described in the schema file
   * Parses the source.txt file
   * Inserts all the data 

 * @date 2022-03-02

 * Make sure that libpqxx and C++ boost libraries are installed on your system.
   (Note that boost library is used only to use a trim() function for data cleaning)
   * sudo apt install libpqxx-dev
   * sudo apt-get install libboost-all-dev
 
 * Instructions to compile and run this program
   * g++ populate_into_db.cpp -o pop -lpqxx
   * ./pop
    Also remember to copy source.txt into the folder where this file is located.
 * If you want to measure time taken to run this program,
   * time ./pop

 * The 'real' time is the time taken by the program
 */

#include <bits/stdc++.h>
#include <pqxx/pqxx>
#include <boost/algorithm/string.hpp>

using namespace std;
using namespace pqxx;

string myPASSWORD = "password";

vector<string> split_authors(string authors)
{
    vector<string> author_names;
    stringstream ss(authors);
    while(ss.good())
    {
        string author;
        getline(ss, author, ',');
        boost::algorithm::trim(author);
        author_names.push_back(author);
    }
    return author_names;
}

vector<tuple<string, string, string>> get_authors(string authors)
{
    vector<string> authorNames = split_authors(authors);
    vector<tuple<string, string, string>> split_names;
    for(auto name : authorNames)
    {
        int first = name.find(' ');
        int last = name.find_last_of(' ');
        string first_name = name.substr(0, first);
        string last_name = name.substr(last+1);
        if(last==-1) last_name = "";
        string middle_name = name.substr(first+1, max(last-first-1, 0));
        boost::algorithm::trim(first_name);
        split_names.push_back(make_tuple(first_name, middle_name, last_name));
    }
    return split_names;
}

void populateData(connection *C){
    cout << "Populating Data into the Database" << endl;
    ifstream input("source.txt");

    C->prepare("insert_paper", 
                "INSERT INTO research_papers (index, title, year, venue, abstract) " \
                "VALUES ($1, $2, $3, $4, $5);");

    C->prepare("insert_author",
                "WITH try_insert AS ("
                    "INSERT INTO authors(first_name, middle_name, last_name) " \
                    "VALUES ($1, $2, $3) " \
                    "ON CONFLICT DO NOTHING " \
                    "RETURNING author_id)" \
                "SELECT * FROM try_insert WHERE EXISTS (SELECT 1 FROM try_insert) " \
                "UNION ALL " \
                "SELECT author_id FROM authors WHERE NOT EXISTS(SELECT 1 from try_insert) AND " \
                "first_name = $1 AND middle_name = $2 AND last_name = $3;");

    C->prepare("insert_auth_paper",
                "INSERT INTO auth_paper(paper_index, author_id, contribution_rank)" \
                "VALUES ($1, $2, $3) " \
                "ON CONFLICT DO NOTHING;");

    C->prepare("insert_citation", 
                "INSERT INTO citations(cited_By, cited)" \
                "VALUES ($1, $2);");

    int n;
    input >> n;
    string line;
    string title, author_names, venue, abstract;
    int index, year;
    vector<int> referenced;
    vector<tuple<string, string, string>> auth_names_list;
    map<int, vector<int>> citation_dictionary;

    time_t t = std::time(nullptr);
    tm *const pTInfo = std::localtime(&t);
    int current_year = pTInfo->tm_year + 1900;

    getline(input, line);
    work W(*C);
    for(int i = 0; i<n; i++)
    {
        title="";
        author_names="";
        venue="";
        referenced.clear();
        abstract="";
        while(getline(input, line, '\n'))
        {
            if(line=="") break;
            switch (line[1])
            {
            case '*':
                title = line.substr(2);
                break;
            case '@':
                author_names = line.substr(2);
                auth_names_list = get_authors(author_names);
                break;
            case 't':
                year = stoi(line.substr(2));
                break;
            case 'c':
                venue = line.substr(2);
                break;
            case 'i':
                index = stoi(line.substr(6));
                break;
            case '%':
                referenced.push_back(stoi(line.substr(2)));
                break;
            case '!':
                 abstract = line.substr(2);
            default:
                break;
            }
        }

        if(year<1800 || year>current_year) continue;

        W.exec_prepared("insert_paper", index, title, year, venue, abstract);
        
        int rank = 1;
        int author_id = 1;
        for(auto author : auth_names_list){
            if(get<0>(author).size()==0) continue;
            string first_name = get<0>(author);
            string middle_name = get<1>(author);
            string last_name = get<2>(author);
            if(first_name.compare("Jr.")==0) continue;
            result R(W.exec_prepared("insert_author", first_name, middle_name, last_name));
            author_id = R.begin()[0].as<int>();
            W.exec_prepared("insert_auth_paper", index, author_id, rank++);
        }
        citation_dictionary[index] = referenced;
    }
    try{
        W.commit();
    }catch (exception &e){
        cerr << e.what() << endl;
    }
    work insertCitations(*C);
    for(auto citation_list : citation_dictionary)
    {
        int cited_by = citation_list.first;
        for(auto cited : citation_list.second)
        {
            insertCitations.exec_prepared("insert_citation", cited_by, cited);
        }
    }
    try{
        insertCitations.commit();
        cout << "Populated database successfully" << endl;
    }catch(exception &e){
        cerr << e.what() << endl;
    }
}

int main(){
        string sql_create_db = \
                "CREATE DATABASE research_papers_db";
        string sql_create_paper = \
                "CREATE TABLE research_papers(" \
                "index      INT            NOT NULL," \
                "title      VARCHAR(1000)  NOT NULL," \
                "year       INT            NOT NULL    CHECK(year>1800 AND year<2100)," \
                "venue      VARCHAR(1000)," \
                "abstract   TEXT," \
                "PRIMARY KEY(index));";

        string sql_create_author = \
                "CREATE TABLE authors(" \
                "author_id   SERIAL," \
                "first_name  VARCHAR(255)      NOT NULL   CHECK(first_name > '')," \
                "middle_name VARCHAR(255)," \
                "last_name   VARCHAR(255)," \
                "PRIMARY KEY(author_id)," \
                "CONSTRAINT unique_names UNIQUE(first_name, middle_name, last_name));";

        string sql_create_auth_paper = \
                "CREATE TABLE auth_paper(" \
                "paper_index         INT   NOT NULL," \
                "author_id           INT   NOT NULL," \
                "contribution_rank   INT   NOT NULL," \
                "CONSTRAINT fk_paper    FOREIGN KEY(paper_index) REFERENCES research_papers(index)," \
                "CONSTRAINT fk_author   FOREIGN KEY(author_id)   REFERENCES authors(author_id)," \
                "PRIMARY KEY(paper_Index, author_id)," \
                "CONSTRAINT unique_contributions UNIQUE(paper_index, contribution_rank));";

        string sql_create_citations = \
                "CREATE TABLE citations(" \
                "cited_by         INT   NOT NULL," \
                "cited            INT," \
                "CONSTRAINT fk_citedby  FOREIGN KEY(cited_by)   REFERENCES research_papers(index)   ON DELETE CASCADE," \
                "CONSTRAINT fk_cited    FOREIGN KEY(cited)      REFERENCES research_papers(index)   ON DELETE CASCADE," \
                "PRIMARY KEY(cited_by, cited));";

        try {
                connection InitialConnection("dbname = template1 user = postgres password = " + myPASSWORD + 
                                            " hostaddr = 127.0.0.1 port = 5432");
                if (InitialConnection.is_open()) {
                        // cout << "Opened database successfully: " << InitialConnection.dbname() << endl;
                        nontransaction CreateDB(InitialConnection);
                        CreateDB.exec(sql_create_db);
                        CreateDB.commit();
                        cout << "Created a database successfully" << endl;
                        InitialConnection.disconnect();
                } else {
                        cout << "Can't open database" << endl;
                        return 1;
                }
                connection C("dbname = research_papers_db user = postgres password = " + myPASSWORD + 
                                            " hostaddr = 127.0.0.1 port = 5432");
                
                if(C.is_open()){
                        cout <<"Opened database successfully: " << C.dbname() << endl;
                }
                else{
                        cout << "Could not open database " << C.dbname() << endl;
                        return 1;
                }
                
                work CreatePaper(C);
                CreatePaper.exec(sql_create_paper);
                CreatePaper.commit();
                
                cout << "Table research_papers created successfully" << endl;

                work CreateAuthor(C);
                CreateAuthor.exec(sql_create_author);
                CreateAuthor.commit();
                
                cout << "Table authors created successfully" << endl;

                work CreateAuthPaper(C);
                CreateAuthPaper.exec(sql_create_auth_paper);
                CreateAuthPaper.commit();

                cout << "Table auth_paper created successfully" << endl;

                work CreateCitations(C);
                CreateCitations.exec(sql_create_citations);
                CreateCitations.commit();

                cout << "Table citations created successfully" << endl;
                
                populateData(&C);
                C.disconnect ();
        }
        catch (const std::exception &e) {
                cerr << e.what() << endl;
                return 1;
        }
}
