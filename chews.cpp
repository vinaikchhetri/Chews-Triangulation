#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <CGAL/Surface_mesh.h>
#include <CGAL/Simple_cartesian.h> 
#include <CGAL/draw_surface_mesh.h>
#include "per.h"

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Point_2<K> Point;
typedef CGAL::Simple_cartesian<double> KK;
typedef CGAL::Surface_mesh<KK::Point_3> Mesh;

using namespace std;


struct HalfEdge;
struct Vertex{
  int index;
  Point p;
  vector<HalfEdge*> incidentEdges= {};
  bool operator == (const Vertex& v) const { return index == v.index;}
 bool operator != (const Vertex& v) const { return !operator==(v); }
 void VertexInit(int num, Point q){index = num; p=q;}
};

struct HalfEdge{
    Vertex* origin = NULL;
    Vertex* target = NULL;
    HalfEdge* prev = NULL;
    HalfEdge* next = NULL;
    HalfEdge* twin = NULL;
    bool operator == (const HalfEdge& h) const { return (*origin == *(h.origin) and *target == *(h.target) );}
    bool operator != (const HalfEdge& h) const { return !operator==(h); }
};

std::ostream& operator<< (std::ostream& os, HalfEdge h);

int getIndex(vector<int> v, int K)
{
    auto it = find(v.begin(), v.end(), K);
    int index = it - v.begin();
    return index;
}

inline std::ostream& operator<< (std::ostream& os, Vertex v)
{
    cout <<"\n"<< "Vertex" << "\n";
    os << "coord:" <<v.p << "\n";
  //   os << "index:" <<v.index << "\n";
  //   os << "incidentEdges:"<<"\n";
  //  for (HalfEdge* e:v.incidentEdges){
  //      cout<<e->origin->p<<"\n";
  //      cout<<e->target->p<<"\n";
  // }
    return os;
}

inline std::ostream& operator<< (std::ostream& os, HalfEdge h)
{
    cout <<"\n"<< "HalfEdge" << "\n";
    // os << "origin:" <<*(h.origin) << "\n";
    // os << "target:" <<*(h.target) << "\n";
    cout<<"<"<<h.origin->index<<" , "<<h.target->index<<">";
    cout<<"\n";
    // cout<<"Printing prev"<<"\n";

    // cout<<*(h.prev->origin);
    // cout<<*(h.prev->target);

    
    // cout<<"Printing next"<<"\n";

    // cout<<*(h.next->origin);
    // cout<<*(h.next->target);

  
    // cout<<"Printing twin"<<"\n";

    // cout<<*(h.twin->origin);
    // cout<<*(h.twin->target);

    return os;
}

inline void printAllEdges(vector<HalfEdge*> edge_list_dcel){
int iter = 0;
for(HalfEdge* he:edge_list_dcel){
    cout<<"new edge: "<<iter<<"\n";
    iter++;
     cout<<"<"<<he->origin->p<<" , "<<he->target->p<<">";
    //cout<<"<"<<he->origin->index<<" , "<<he->target->index<<">";
    cout<<"\n";

    // cout<<"prev"<<"\n";
    // cout<<"<"<<he.prev[0]->origin->p<<" , "<<he.prev[0]->target->p<<">";
    // cout<<"\n";

    // cout<<"next"<<"\n";
    // cout<<"<"<<he.next[0]->origin->p<<" , "<<he.next[0]->target->p<<">";
    // cout<<"\n";

    // cout<<"twin"<<"\n";
    // if(he.twin.empty())
    //     cout<<"empty twin"<<"\n";
    // else
    //     cout<<"<"<<he.twin[0]->origin->p<<" , "<<he.twin[0]->target->p<<">"<<"\n";
     }
}

inline std::ostream& operator<< (std::ostream& os, vector<vector<int>> vec)
{
    os <<"\n"<< "Matrix" << "\n";
    
    for (int i=0; i<vec.size(); i++){
        for(int j=0; j<vec[0].size(); j++){
            os << vec[i][j] << " ";
        }
        os<<"\n";
    }
  
    return os;
}

inline std::ostream& operator<< (std::ostream& os, vector<int> l)
{
    cout <<"\n"<< "vector of int" << "\n";
    
    for (int i:l){
        os << i << "\n";
    }
  
    return os;
}

inline std::ostream& operator<< (std::ostream& os, vector<Vertex> l)
{
    cout <<"\n"<< "vector of vertices" << "\n";
    
    for (Vertex i:l){
        os << i << "\n";
    }
  
    return os;
}

template <typename T> inline T* access (list<T> vertices, int index)
{
   
    auto l_front = vertices.begin();

    advance(l_front, index);

 
    return &(*l_front);
}

inline list<int> splice (list<int> vertices, int index1, int index2)
{
    list<int>::iterator it = vertices.begin();
    list<int>::iterator itp = vertices.begin();
    advance(it,index1);
    advance(itp,index2);
    list<int> b(it, itp);
    return b;
}

vector<Vertex*> vertices_dcel = {};
vector<HalfEdge*> edge_list_dcel = {};

inline void swap_test_dcel(int aIndex, int bIndex, int cIndex){
    
    Vertex* a = vertices_dcel[aIndex];
    Vertex* b = vertices_dcel[bIndex];
    Vertex* c = vertices_dcel[cIndex];
    HalfEdge* x;
    Vertex* d;
    HalfEdge* add_edge_dcel_1;
    HalfEdge* add_edge_dcel_2;
    int ct;

    cout<<aIndex<<" "<<bIndex<<" "<<cIndex<<"\n";
    for(HalfEdge* y:c->incidentEdges){

        if (*(y->target) == *b && !(y->twin==NULL)){
        cout<<"here ";

        if(*(y->twin->next->next->target) == *b){
            x = y->twin->next;
            d = x->target;
            cout<<"a: ,"<< (a->index)<<"\n";
            cout<<"b: ,"<< (b->index)<<"\n";
            cout<<"c: ,"<< (c->index)<<"\n";
            cout<<"d: ,"<< (d->index)<<"\n";
            //side_of_bounded_circle
            ct = side_of_bounded_circle(b->p, c->p, d->p, a->p);
            cout<<"\n"<<"in-circle test "<<ct<<"\n";
            
            if(ct==1){
                cout<<"flip bc to ad: "<<b->index<<" "<< c->index<< " to : "<<a->index<<" "<<d->index<<"\n";
                add_edge_dcel_1 = new HalfEdge();
                add_edge_dcel_1->origin = a; 
                add_edge_dcel_1->target = d; 
                add_edge_dcel_1->prev = y->next;
                add_edge_dcel_1->next = x->next;

                add_edge_dcel_2 = new HalfEdge();
                add_edge_dcel_2->origin = d; 
                add_edge_dcel_2->target = a; 
                add_edge_dcel_2->prev = x;
                add_edge_dcel_2->next = y->prev;

                add_edge_dcel_1->twin = add_edge_dcel_2;
                add_edge_dcel_2->twin = add_edge_dcel_1;
                
                (c->incidentEdges).erase(std::remove((c->incidentEdges).begin(), (c->incidentEdges).end(), y), (c->incidentEdges).end());
                (b->incidentEdges).erase(std::remove((b->incidentEdges).begin(), (b->incidentEdges).end(), y->twin), (b->incidentEdges).end());
                a->incidentEdges.push_back(add_edge_dcel_1);
                d->incidentEdges.push_back(add_edge_dcel_2);
                
                (x->next) = add_edge_dcel_2;
                (x->prev) = (y->prev);
                (y->prev->next) = x;
                (y->prev->prev) = add_edge_dcel_2;

                y->next->next = add_edge_dcel_1;
                y->next->prev  = (y->twin->prev);
                y->twin->prev->next = (y->next);
                y->twin->prev->prev = add_edge_dcel_1;

         
                (edge_list_dcel).erase(std::remove((edge_list_dcel).begin(), (edge_list_dcel).end(), y), (edge_list_dcel).end());
                (edge_list_dcel).erase(std::remove((edge_list_dcel).begin(), (edge_list_dcel).end(), y->twin), (edge_list_dcel).end());
    
                edge_list_dcel.push_back(add_edge_dcel_1);
                edge_list_dcel.push_back(add_edge_dcel_2);
                
                cout<<"propagate swap test to adc "<<a->index<<" "<<d->index<<" "<<c->index;
                swap_test_dcel(a->index, d->index, c->index);
                cout<<"propagate swap test to abd "<<a->index<<" "<<b->index<<" "<<d->index;
                swap_test_dcel(a->index, b->index, d->index);

            }
            else
                cout<<"\n"<<"No flips"<<"\n";

        }
      } 

    }
}
 
int main()
{


     vector<Vertex> vertices;
     Vertex p,q,r,s,t,tt;
//      p.VertexInit(0,Point(0, 0.3));
//      q.VertexInit(1,Point(0.7, 0.6));
//      r.VertexInit(2,Point(0.8,0.4));
//      s.VertexInit(3,Point(0.7, 0.2));
    
//     p.VertexInit(0,Point(0.2, 0.1));
//     q.VertexInit(1,Point(0.4, 0.1));
//     r.VertexInit(2,Point(0.6,0.3));
//     s.VertexInit(3,Point(0.4, 0.5));
//     t.VertexInit(4,Point(0.2, 0.5));
//     tt.VertexInit(5,Point(0.1, 0.3));
    
//      p.VertexInit(0,Point(0, 0.3));
//      q.VertexInit(1,Point(0.7, 0.6));
//      r.VertexInit(2,Point(0.8,0.3));
//      s.VertexInit(3,Point(0.7, 0.2));
//      t.VertexInit(4,Point(0.5, 0.01));
//      tt.VertexInit(5,Point(0.1, 0.01));
    
        p.VertexInit(0,Point(0, 0));
        q.VertexInit(1,Point(0, 0.8));
        r.VertexInit(2,Point(0.8,0.8));
        s.VertexInit(3,Point(0.3, 0));
        t.VertexInit(4,Point(0.1, 0));



     vertices.push_back(p);
     vertices.push_back(q);
     vertices.push_back(r);
     vertices.push_back(s);
     vertices.push_back(t);
//     vertices.push_back(tt);
    
    
    vector<int> vertex_indices;
    for(int i = 0; i <vertices.size(); i++){
        vertex_indices.push_back(i);
    }


    vector<int> rand_indices = generateRandom(vertices.size());

    vector<vector<int>> neighbours_stack_id;
    int neighbourNext,neighbourPrev;

    for (int i:rand_indices){
        int index = getIndex(vertex_indices, i);
        if (index==0){
            neighbourNext = vertex_indices[(index+1)%vertex_indices.size()];
            neighbourPrev = vertex_indices[vertex_indices.size()-1];
        }
        else{
            neighbourNext = vertex_indices[(index+1)%vertex_indices.size()];
            neighbourPrev = vertex_indices[(index-1)%vertex_indices.size()];
        }


        neighbours_stack_id.push_back({neighbourPrev,neighbourNext});
        vertex_indices.erase(vertex_indices.begin()+index,vertex_indices.begin()+index+1);
        if (vertex_indices.size() <= 3)
            break;
    }
 

    reverse(neighbours_stack_id.begin(), neighbours_stack_id.end());
    reverse(rand_indices.begin(), rand_indices.end());
    vector<int> base_vertex_id (rand_indices.begin(), rand_indices.begin()+3);
    sort(base_vertex_id.begin(), base_vertex_id.end());
    cout<<"base_vertex_id"<<base_vertex_id;
    
    Vertex* v;
    for (Vertex i:vertices){
        v = new Vertex();
        v->index = i.index;
        v->p = i.p;
        vertices_dcel.push_back(v);
    }
  
    HalfEdge* h;
    for(int i=0; i<base_vertex_id.size(); i++){
        h = new HalfEdge();
        if (i==base_vertex_id.size()-1){
            h->origin = vertices_dcel[base_vertex_id[i]];
            h->target = vertices_dcel[base_vertex_id[0]];            
        }
        else{
            h->origin = vertices_dcel[base_vertex_id[i]];
            h->target = vertices_dcel[base_vertex_id[i+1]];            
        }
        edge_list_dcel.push_back(h);
     }


    Vertex* ret;
    for (auto vertex_id:base_vertex_id){
        ret = vertices_dcel[vertex_id];
        for (HalfEdge* edge:edge_list_dcel){
            if (*(edge->origin) == *ret){
                 ret->incidentEdges.push_back(edge);
            }
                
        }
    }

    HalfEdge* rete;
    for(int i=0; i<edge_list_dcel.size(); i++){
        rete = edge_list_dcel[i];

        if(i==0){
            rete->next = edge_list_dcel[(i+1)%edge_list_dcel.size()];
            rete->prev = edge_list_dcel[edge_list_dcel.size()-1];
        }
        else{
            rete->next = edge_list_dcel[(i+1)%edge_list_dcel.size()];
            rete->prev = edge_list_dcel[(i-1)%edge_list_dcel.size()];
        }
    }
    

  Vertex* addVertexDcel;
  Vertex* addVertexPrevDcel;
  Vertex* addVertexNextDcel;
  HalfEdge* addEdgePrevDcel;
  HalfEdge* addEdgeNextDcel;
  HalfEdge* addEdgeOppDcel;
  vector<HalfEdge*> addEdgeList;
  vector<HalfEdge> taddEdgeList;
  int  counter=3;
  for(int id=0; id<rand_indices.size()-3; id++){
      addEdgeList = {};
      addVertexDcel = vertices_dcel[rand_indices[id+3]];
      addVertexPrevDcel = vertices_dcel[neighbours_stack_id[id][0]];
      addVertexNextDcel = vertices_dcel[neighbours_stack_id[id][1]];

      addEdgePrevDcel = new HalfEdge();
      addEdgePrevDcel->origin = addVertexPrevDcel;
      addEdgePrevDcel->target = addVertexDcel;
     
      addEdgeNextDcel = new HalfEdge();
      addEdgeNextDcel->origin = addVertexDcel;
      addEdgeNextDcel->target = addVertexNextDcel;
      
      addEdgeOppDcel = new HalfEdge();      
      addEdgeOppDcel->origin = addVertexNextDcel;
      addEdgeOppDcel->target = addVertexPrevDcel;

      
      addEdgePrevDcel->prev = (addEdgeOppDcel);
      addEdgePrevDcel->next = (addEdgeNextDcel);
      addEdgePrevDcel->origin->incidentEdges.push_back(addEdgePrevDcel);
      
      
      addEdgeNextDcel->prev = (addEdgePrevDcel);
      addEdgeNextDcel->next = (addEdgeOppDcel);
      addEdgeNextDcel->origin->incidentEdges.push_back(addEdgeNextDcel);
      
      
      addEdgeOppDcel->prev = (addEdgeNextDcel);
      addEdgeOppDcel->next = (addEdgePrevDcel);
      addEdgeOppDcel->origin->incidentEdges.push_back(addEdgeOppDcel);

      for (HalfEdge* x:addEdgeOppDcel->target->incidentEdges){
          if (x->target == addEdgeOppDcel->origin){
              addEdgeOppDcel->twin = (x);
              x->twin = (addEdgeOppDcel);

          }
      }


      addEdgeList.push_back(addEdgePrevDcel);
      addEdgeList.push_back(addEdgeNextDcel);
      addEdgeList.push_back(addEdgeOppDcel);
      counter+=3;
      edge_list_dcel.insert(edge_list_dcel.end(), addEdgeList.begin(), addEdgeList.end());
      swap_test_dcel(addVertexDcel->index, addVertexPrevDcel->index, addVertexNextDcel->index);

  }


printAllEdges(edge_list_dcel);
cout<<"\n"<<"------------------"<<"\n";

Mesh m;
Vertex vv;
Vertex uu;
Vertex ww;
Mesh::Vertex_index uuu;
Mesh::Vertex_index vvv;
Mesh::Vertex_index www;
cout<<"counter "<<counter<<"\n";
for(Vertex* ver:vertices_dcel){
    for(HalfEdge* haf:ver->incidentEdges){
        uu = *(haf->origin);
        vv = *(haf->next->origin);
        ww = *(haf->next->next->origin);
        // cout<<uu.p<<"\n";
        // cout<<uu.p<<"\n";
        // cout<<uu.p<<"\n";
        uuu = m.add_vertex(KK::Point_3(uu.p.x(),uu.p.y(),0));
        vvv = m.add_vertex(KK::Point_3(vv.p.x(),vv.p.y(),0));
        www = m.add_vertex(KK::Point_3(ww.p.x(),ww.p.y(),0)); 
        m.add_face(uuu, vvv, www);
    }
}
 

CGAL::draw(m);

int ct;
for(Vertex* ver:vertices_dcel){
    for(HalfEdge* haf:ver->incidentEdges){
        cout<<"\n"<<"triangle"<<"\n";
        uu = *(haf->origin);
        vv = *(haf->next->origin);
        ww = *(haf->next->next->origin);
        for(Vertex* ver:vertices_dcel){
            ct = side_of_bounded_circle(uu.p, vv.p, ww.p, ver->p);
            
            cout<<"\n"<<"in-circle test "<<ct<<"\n";
        }

    }
}
}
