#include <bits/stdc++.h>

using namespace std;

ifstream f("abce.in");
ofstream g("abce.out");

struct nod{
    int val;
    nod *next;
    nod *down;
    nod(const int &value){
        val=value;
        next= nullptr;
        down= nullptr;
    }
};

class SkipList{
    vector<nod*> start;
    int level,maxLevel;
    nod* Search(int &value){
        nod *first;
        first=start.back();
        while(first!= nullptr){
            if(first->val==value)
                return first;
            else
                if(first->val<value && first->next->val<=value)
                    first=first->next;
                else
                    if(first->val<value && first->next->val>value)
                        first=first->down;
        }
        return first;
    }
    void PrintSkipList(){
        for(int i=level;i>=0;--i){
            cout<<"Level "<<i<<":\n";
            nod *first=start[i]->next;
            while(first->next!= nullptr){
                cout<<first->val<<' ';
                first=first->next;
            }
            cout<<'\n';
        }
    }
public:
    SkipList(int maxL){
        maxLevel=maxL;
        nod *limInf= new nod(INT_MIN);
        nod *limSup= new nod(INT_MAX);
        level=0;
        limInf->next=limSup;
        limInf->down= nullptr;
        limSup->next= nullptr;
        limSup->down= nullptr;
        start.push_back(limInf);
    }
    int SearchNode(int &value){
        if(Search(value)== nullptr)
            return 0;
        return 1;
    }
    int SearchMax(int &value){
        nod *first;
        int sol;
        first=start.back();
        while(first!= nullptr){
            if(first->val==value)
                return first->val;
            else
                if(first->val<value && first->next->val<=value) {
                    sol=first->next->val;
                    first = first->next;
                }
                else
                    if(first->val<value && first->next->val>value) {
                        sol= first->val;
                        first = first->down;
                    }
        }
        return sol;
    }
    int SearchMin(int &value){
        nod *first;
        int sol;
        first=start.back();
        while(first!= nullptr){
            if(first->val==value)
                return first->val;
            else
                if(first->val<value && first->next->val<=value) {
                    first = first->next;
                }
                else
                    if(first->val<value && first->next->val>value) {
                        sol= first->next->val;
                        first = first->down;
                    }
        }
        return sol;
    }
    void PrintInterval(int &x,int &y){
        nod *first,*sol;
        first=start.back();
        while(first!= nullptr){
            if(first->val==x) {
                sol = first;
                break;
            }
            else
                if(first->val<x && first->next->val<=x) {
                    first = first->next;
                }
                else
                    if(first->val<x && first->next->val>x) {
                        sol= first->next;
                        first = first->down;
                    }
        }
        while(sol->down!=nullptr){
            sol=sol->down;
        }
        g<<sol->val<<' ';
        while(sol->next!= nullptr && sol->next->val<=y){
            g<<sol->next->val<<' ';
            sol=sol->next;
        }
        g<<'\n';
    }
    void DeleteNode(int &value){
        nod *first;
        first=start.back();
        while (first->next!= nullptr){
            if(first->next->val==value){
                nod *aux;
                aux=first->next;
                first->next=first->next->next;
                delete aux;
                if(first->down== nullptr)
                    return;
                else
                    first=first->down;
            }
            else
                if(first->next->val<value)
                    first=first->next;
                else{
                    if(first->down== nullptr)
                        return;
                    else
                        first=first->down;
                }
        }
    }
    void InsertNode(int &value){
        int currLevel=0;
        vector<nod*> update;
        nod *insert=new nod(value);
        nod *first,*down= nullptr,*aux;
        first=start.back();
        while(first!= nullptr){
            while(first->next!= nullptr && first->next->val<value){
                first=first->next;
            }
            update.push_back(first);
            first=first->down;
        }

        aux=update.back();

        insert->next=aux->next;
        aux->next= insert;
        insert->down=down;
        down=insert;

        update.pop_back();


        float coin = (float)rand()/RAND_MAX;
        bool nivCreat;
        while(coin<0.5 && currLevel<maxLevel){
            currLevel++;
            nivCreat=false;
            if(level<currLevel){
                level++;
                nivCreat=true;
                nod *limInf=new nod(INT_MIN);
                nod *limSup=new nod(INT_MAX);
                limInf->next=limSup;
                limInf->down=start.back();
                limSup->next= nullptr;
                limSup->down= nullptr;
                start.push_back(limInf);
            }
            nod *insert=new nod(value);

            if(nivCreat) {
                aux=start.back();
            }
            else{
                aux = update.back();
            }

            insert->next=aux->next;
            aux->next= insert;
            insert->down=down;
            down=insert;

            if(!nivCreat) {
                update.pop_back();
            }

            coin = (float)rand()/RAND_MAX;
        }

    }
};

int main() {

    int Q,op,x,y;
    f>>Q;

    SkipList skip((int)log(Q));


    for(int i=0;i<Q;++i){
        f>>op>>x;
        if(op==1){
            skip.InsertNode(x);
        }
        else
            if(op==2){
                skip.DeleteNode(x);
            }
            else
                if(op==3){
                    g<<skip.SearchNode(x)<<'\n';
                }
                else
                    if(op==4){
                        g<<skip.SearchMax(x)<<'\n';
                    }
                    else
                        if(op==5){
                            g<<skip.SearchMin(x)<<'\n';
                        }
                        else{
                            f>>y;
                            skip.PrintInterval(x,y);
                        }
    }

    f.close();
    g.close();

    return 0;
}
