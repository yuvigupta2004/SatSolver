#include <bits/stdc++.h>
using namespace std;



int check_clause_status(vector<int> clause, map<int,int> variable_assignment){

   
    int k=0;
    
    for(int literal : clause){
        
        if(variable_assignment[abs(literal)]!= 0){
            k++;
            if(variable_assignment[abs(literal)] * literal < 0){
                continue;
            }
            return 1;
        }
    }
    if(k==clause.size()){
        return -1;
    }
    return 0;
}


int check_formula_status (vector<vector<int>> clauses, map<int,int> variable_assignment){
    
    bool unassignedfound = true;
    for(auto clause : clauses){
        int result = check_clause_status(clause, variable_assignment);
        if(result == -1){
            return -1;
        }
        
        else if(result == 0){
            unassignedfound = false;
        }
    }
    return unassignedfound;
}


int number_of_unassigned_variables(vector<int> clause, map<int,int> variable_assignment){
    int count = 0;
    for(int literal : clause){
        if(variable_assignment[abs(literal)] == 0){
            count++;
        }
    }
    return count;
}



int unit_propogation(vector<vector<int>>& clauses, map<int,int>& variable_assignment){
    while(true){
            // cout<<"Stuck in a loop?"<<endl;
            for(int i=0;i<clauses.size();i++){
                auto clause = clauses[i];
                if(check_clause_status(clause, variable_assignment)==-1){
                        return -1;
                        // Conflict Mil gaya
                }

                if(check_clause_status(clause, variable_assignment)==1){
                    if (i==clauses.size()-1){
                        return check_formula_status(clauses, variable_assignment);
                    }   
                    continue;
                }

                if(number_of_unassigned_variables(clause, variable_assignment)==1){  
                    
                    for(auto x : clause){
                        if (variable_assignment[abs(x)]==0){
                            variable_assignment[abs(x)] = x>0? 1 : -1;
                            break;
                        }
                    }
                    break;  
                }  

                if (i==clauses.size()-1){
                   return check_formula_status(clauses, variable_assignment);
                }   
            }
            // All unit literal and unit propogation done
    }
    // now we take a decision since we are done with unit propogation    
}


int main(){


    ifstream inputFile("clauses.txt");
    
    if (!inputFile.is_open()) {
        cout << "Failed to open file." << endl;
        return 1;
    }

    vector<vector<int>> clauses;
    set<int> setofvariables;

    string line;
    while (getline(inputFile, line)) {
        vector<int> clause;
        stringstream ss(line);
        int literal;

        while (ss >> literal) {
            clause.push_back(literal);
            setofvariables.insert(abs(literal));
        }

        clauses.push_back(clause);
    }

    inputFile.close();


    // cout << "Clauses: " << endl;
    // for (const auto& clause : clauses) {
    //     for (int literal : clause) {
    //         cout << literal << " ";
    //     }
    //     cout << endl;
    // }

    // cout << "Set of variables: " << endl;
    // for (int var : setofvariables) {
    //     cout << var << " ";
    // }
    // cout << endl;



    
    map<int, int> variable_assignment;
    stack<map<int,int>> variable_assignment_stack;

    

    for ( auto x : setofvariables){
        variable_assignment[x] = 0;  // undecided
    }
    // it is 0 if unassigned, -1 if false and 1 if true
    // I have a set of all the variables, i have their assignment in a vector(undecided for now), i have a set of clauses where each clause is a set of the literals in it  
    

    // cout<<"First Unit Propogation done"<<endl;
    vector<int> decisions_taken;

    // cout<<"Second Unit Propogation done"<<endl;
    int result = unit_propogation(clauses, variable_assignment);

    variable_assignment_stack.push(variable_assignment);

    if(result==-1){
        cout<<"UNSAT"<<endl;
        return 0;
    }

    while(true){
        
    
        // now I take a decision
        
        for(auto x : variable_assignment){
            if(x.second==0){
                
                variable_assignment[x.first] = 1 ;
                decisions_taken.push_back(x.first);
                // cout<<"Decision Taken: "<<x.first<<endl;
                break;
            }
        }

        result = unit_propogation(clauses, variable_assignment);
        variable_assignment_stack.push(variable_assignment);


        if(result == 0){
            continue;
        }


        while(result==-1){

            variable_assignment_stack.pop();
            if(variable_assignment_stack.size()==0){
                cout<<"UNSAT"<<endl;
                return 0;
            }
            variable_assignment = variable_assignment_stack.top();

            
            vector<int> learnt_clause;
            if(decisions_taken.size()==0){
                cout<<"UNSAT"<<endl;
                return 0;
            }
            for(auto x : decisions_taken){
                learnt_clause.push_back(-1*x);
            }
            // for(auto x : learnt_clause){
            //     cout<<x<<" ";
            // }
            // cout<<endl;
            auto decisiontopop = decisions_taken[decisions_taken.size()-1];
            decisions_taken.pop_back();
            clauses.push_back(learnt_clause);
            // cout<<"No Seg"<<endl;
            result = unit_propogation(clauses,variable_assignment);

        
        }

        
        if(result==1){
            cout<<"SAT"<<endl;
            return 0;
        }

        
        
    }
    

}



  