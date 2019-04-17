#include<iostream>
#include<vector>
#include<cmath>
#include<iomanip>
#include<fstream>

#include"meshGeneration.h"
using std::cout; using std::endl;
using std::cin;  using std::setw;
using std::make_pair;



meshGeneration::meshGeneration(void):NI(40),NJ(20),_lenX(2+sqrt(2.0)),_lenY(sqrt(2.0))
{
deltH=new double[NJ];}

// std::vector<std::pair<double,double>> _north,_south,_west,_east;
//the xy-coordination was set at the left-down point of the domain
void meshGeneration::boundarySeeds(){
std::ofstream fout1("seeds.dat");
fout1<<"x"<<setw(15)<<"y"<<endl;

   for(int i=0;i<NI+1;++i){
        if(i<=10){
            _north.push_back(make_pair(i*0.1,_lenY));
            _south.push_back(make_pair(i*0.1,0.0));

        continue;}
        else if(i<30){
             xtmp=1+sqrt(2)/20*(i-10);
             ytmp1=0.707106+sqrt(1-(xtmp-1.707106)*(xtmp-1.707106));
            _north.push_back(make_pair(xtmp,ytmp1));
             ytmp2=0.707106-sqrt(1-(xtmp-1.707106)*(xtmp-1.707106));
            _south.push_back(make_pair(xtmp,ytmp2));

        continue;}
        else{
                xtmp=1+sqrt(2.0)+0.1*(i-30);
            _north.push_back(make_pair(xtmp,_lenY));
            _south.push_back(make_pair(xtmp,0.0));
        continue;}
}
std::vector<std::pair<double,double>>::iterator iter1,iter2;
 for(iter1=_south.begin();iter1!=_south.end();iter1++)
    {
        cout<<iter1->first<<setw(15)<<iter1->second<<endl;
        fout1<<iter1->first<<setw(15)<<iter1->second<<endl;
    }
for(iter2=_north.begin();iter2!=_north.end();iter2++)
    {
        cout<<iter2->first<<setw(15)<<iter2->second<<endl;
        fout1<<iter2->first<<setw(15)<<iter2->second<<endl;
    }

     deltH[0]=0.0461156;//first delta h
     ytmp=0;
    for(int j=0;j<NJ+1;++j){

    ytmp=ytmp+deltH[j];
         if(j<=7){
        deltH[j+1]=deltH[j]*1.1;
         _west.push_back(make_pair(0.0,ytmp));
        _east.push_back(make_pair(_lenX,ytmp));
         continue;}
         else if(j<12){
        deltH[j+1]=deltH[j];
         _west.push_back(make_pair(0.0,ytmp));
         _east.push_back(make_pair(_lenX,ytmp));
         continue;}
         else {
        deltH[j+1]=deltH[j]/1.1;
         _west.push_back(make_pair(0.0,ytmp));
         _east.push_back(make_pair(_lenX,ytmp));
         continue;}
    }

       for(int i=0;i<_west.size();++i){
        cout<<_west[i].first<<setw(15)<<_west[i].second<<endl;
        fout1<<_west[i].first<<setw(15)<<_west[i].second<<endl;
        }

    for(int i=0;i<_east.size();++i){
        cout<<_east[i].first<<setw(15)<<_east[i].second<<endl;
        fout1<<_east[i].first<<setw(15)<<_east[i].second<<endl;
        }
 }

void  meshGeneration::bi_LogicalInterpolation(){
    std::ofstream fout2("mesh1.dat");
for(int i=1;i<NI;++i){
    for(int j=1;j<NJ;++j){
            xa=(1-(double)i/40)*_west[j].first+(double)i/40*_east[j].first;
            xb=(1-(double)j/20)*_north[i].first+(double)j/20*_south[i].first;
            xc=(double)i/40*(1-(double)j/20)*_south[39].first+(double)i/40*(double)j/20*_north[39].first;

            ya=(1-(double)i/40)*_west[j].second+(double)i/40*_east[j].second;
            yb=(1-(double)j/20)*_north[i].second+(double)j/20*_south[i].second;
            yc=(double)i/40*(1-(double)j/20)*_north[39].second+(double)i/40*(double)j/20*_north[39].second;

            xtmp=xa+xb-xc;
            ytmp=ya+yb-yc;

            _inner.push_back(make_pair(xtmp,ytmp));

    }
}
        for(int i=0;i<_west.size();++i){
        cout<<_west[i].first<<setw(15)<<_west[i].second<<endl;
        fout2<<_west[i].first<<setw(15)<<_west[i].second<<endl;
        }
        for(int i=0;i<_east.size();++i){
        cout<<_east[i].first<<setw(15)<<_east[i].second<<endl;
        fout2<<_east[i].first<<setw(15)<<_east[i].second<<endl;
        }
        for(int i=0;i<_north.size();++i){
        cout<<_north[i].first<<setw(15)<<_north[i].second<<endl;
        fout2<<_north[i].first<<setw(15)<<_north[i].second<<endl;
        }
        for(int i=0;i<_south.size();++i){
        cout<<_south[i].first<<setw(15)<<_south[i].second<<endl;
        fout2<<_south[i].first<<setw(15)<<_south[i].second<<endl;
        }
      for(int i=0;i<_inner.size();++i){
        cout<<_inner[i].first<<setw(15)<<_inner[i].second<<endl;
        fout2<<_inner[i].first<<setw(15)<<_inner[i].second<<endl;
        }

}









int main(){
    meshGeneration mesh1;
    mesh1.boundarySeeds();
    mesh1.bi_LogicalInterpolation();
}

