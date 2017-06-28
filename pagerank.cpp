//Parallel processing Assignment 
//Authors: Snigdh Gupta(149105462) & SumitKumar Yadav(149105478) ,02-04-2017 , 4:16pm
//CSE SEC C
//to compile : g++ pagerank.cpp -std=c++0x
//parallel code
#include <omp.h>
#include <bits/stdc++.h>

using namespace std;
int main(int argc, char const *argv[])
{
  //int i;
  string str;
  // ofstream fo("/var/www/html/pagerank/display.php");
  ofstream fo2("/var/www/html/pagerank/insert.php");
       
              //omp_set_nested(1);
              //omp_set_dynamic(0);

  string list[10000][6];
  std::fill(list[0], list[0] + 10000 * 6, "0");
  int count = 0;
  int temp;

  fo2 << "<?php include('config.php'); "<<endl;
  //fo2<< "DELETE FROM list"<<endl;
      
    double start_time = omp_get_wtime();
    #pragma omp parallel for private(temp)  num_threads(5) 
        for(int j=1;j<=5;j++)
           { 
              string temp3;
              temp3 = "file" + to_string(j) + ".txt";
              ifstream fi(temp3);   //"file" + temp2 + ".txt"

                  while (fi >> str)
                  {   
                    int flag=0;
                    int i;
                    int temp23;
                    int flag2 = 1;
                       #pragma omp parallel for 
                          for (i = 0; i < count; ++i)
                              { 
                                  if(list[i][0]==str&&flag2==1)
                                  { //int b = atoi(a.c_str());
                                    flag=1;
                                    temp = atoi(list[i][j].c_str());//(int)list[i][j];
                                    temp++;

                                                                 //fo2<<str<<"$var=" << temp;
                                        fo2<<"$query = \"UPDATE `list` SET `"<<j<<"`="<<temp<<" WHERE `string`='"<<str<<"';\";"<<endl;
                                        fo2<<"mysqli_query($con,$query);"<<endl;




                                                stringstream convert; 

                                                convert << temp; 

                                                list[i][j] = convert.str();
                                                flag2 = 0;
                                                //break;

                                  }


                             }
                          

                
                if(flag==0)
                  {
                                            //count++;
                       //#pragma omp critical 
                           {
                              list[count][0] = str;
                              list[count][j] = '1';
                              count++;

                              fo2 << "$var=\""<<str<<"\";"<<"\n";
                              fo2 << "$query = \"INSERT INTO `list`(`string`,`"<<j<<"`)VALUES ('\".$var.\"',1);\";"<<endl;
                              fo2 << "mysqli_query($con,$query);"<<endl;
                           }
 
          
                  }
      
         

    }
  }

   

  
fo2<<"header(\"Location:display.php\");?>";


  /*for (int i = 0; i < count; ++i)
  {
    //cout<<left<<setw(15)<<list[i][0]<<setw(4)<<list[i][1]<<setw(4)<<list[i][2]<<setw(4)<<list[i][3]<<endl;
    for (int j = 0; j < 4; ++j)
    {
      cout<<left<<setw(5)<<list[i][j]<<"    ";
    }
    cout<<endl;
  }*/
 //cout<<count;

string str1;
double time = omp_get_wtime() - start_time;

cout<<"Enter the term to be searched:"<<endl;
cin>>str1;
int flag1=0;
int result;

//#pragma omp parallel for
for (int i = 0; i < count; ++i)
{
  if(list[i][0] == str1)
  {
    flag1=1;
    result = i;
    break;
  }
}



if(flag1==0)
  cout<<"No Results Found!!!"<<endl;

else
{

  vector< pair<int, int> > v;
  vector< pair<int, int> >::iterator it;

  for (int i = 0; i < 5; ++i)
  {
    v.push_back(make_pair(atoi(list[result][i+1].c_str()),i+1));
    
      //atoi(list[result][i+1].c_str())
  }
  sort(v.rbegin(),v.rend());
  int index=1;
  //cout<<"Rank"<<"\t"<<"Document"<<"\t"<<"frequency"<<endl;
for(it=v.begin();it!=v.end();it++)
{
  //cout<<"frequency=>"<<it->first << "  " <<" doc.ID=>"<<it->second<<endl;
  //cout<<index++<<"=> "<<setw(10)<<"file"<<it->second<<".text"<<setw(10)<<it->first<<endl;
}

  v.clear();
  
}
//list[count][i+1]

  


  printf("%lf",time);
  return 0;
}
