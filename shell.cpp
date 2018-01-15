#include <iostream>
#include "atom.h"
#include "variable.h"
#include "global.h"
#include "scanner.h"
#include "struct.h"
#include "list.h"
#include "exp.h"
#include "parser.h"

using std::string;

int main(){
    string express="";
    char c;


    std::cout<<"?- ";

        while(1){

            while((c=getchar())){
                if(c == '\n' && express == ""){
                    std::cout<<"?- ";
                    continue;
                }
                else if(c == '\n'){
                    std::cout<<"|   ";
                    continue;
                }
                express=express+c;

                if(express.at(express.size()-1)=='.'){
                    break;
                }
            }

            if(express.compare("halt.")==0)
                break;
            try {
                Scanner s(express);
                Parser p(s);
                p.buildExpression();
                std::cout<<p.getExpressionTree()->getEvaluateString()+"."<<std::endl;
            }catch (string &msg) {
                std::cout<<msg<<std::endl;
            }
            
    
            express.clear();
        }
}