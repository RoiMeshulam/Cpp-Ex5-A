#ifndef EX5_PARTA_ORGCHART_H
#define EX5_PARTA_ORGCHART_H

#endif //EX5_PARTA_ORGCHART_H
#include <iostream>
#include <vector>
#include <list>

#pragma once

using namespace std;

namespace ariel{

    class OrgChart {
    public:
        struct Node {
            string _value;
            Node* _next;
            bool _visited;
            vector<Node*> _children;
            Node(string value): _value(value),_visited(false), _next(nullptr),_children() {}
        };




        Node* _root;
        Node* _tail;
        vector<Node*> _allNodes;
        vector<Node*> _preOrder;

        OrgChart():_root(nullptr),_tail(nullptr),_preOrder(),_allNodes(){
            cout<< "OrgChart was created"<<endl;
        }
        ~OrgChart(){

        }
        OrgChart& add_root(const string root);
        OrgChart& add_sub(const string root,const string child );
        friend ostream& operator<<(ostream& out, const OrgChart& OrgChart);
        void BFS();
        void revBFS();
        void DFS();
        void DFS_Visit(Node* curr);



        //inner class LevelIterator:
        class OrgChartIterator {
        private:
            Node* _current_node;

        public:
            OrgChartIterator(Node* ptr = nullptr): _current_node(ptr) {
            }

            Node* operator&(){
                return _current_node;
            }

            string& operator*() const {
                //return *pointer_to_current_node;
                return _current_node->_value;
//                return "hi";
            }

            string* operator->() const {
                return &(_current_node->_value);
            }

            // ++i;
            OrgChartIterator& operator++() {
                //++pointer_to_current_node;
                _current_node = _current_node->_next;
                return *this;
            }

            // i++;
            // Usually iterators are passed by value and not by const& as they are small.
            const OrgChartIterator operator++(int) {
                OrgChartIterator tmp= *this;
                _current_node= _current_node->_next;
                return tmp;
            }

            bool operator==(const OrgChartIterator& rhs) const {
                return _current_node == rhs._current_node;
            }

            bool operator!=(const OrgChartIterator& node) const {
                return _current_node != node._current_node;
            }
        };  // END OF CLASS OrgChartIterator


        OrgChartIterator begin_level_order(){
            this->BFS();
            return OrgChartIterator{_root};
        }
        OrgChartIterator end_level_order(){
            return nullptr;
        }

        OrgChartIterator begin_reverse_order(){
            this->revBFS();
            return OrgChartIterator{_tail}; // should be replaced because we iterate from the end of the OrgChart.
        }

        OrgChartIterator reverse_order(){
            return nullptr;
        }

        OrgChartIterator begin_preorder(){
            _preOrder.clear();
            this->DFS();
            for (size_t i = 0; i <_preOrder.size()-1 ; ++i) {
                _preOrder.at(i)->_next = _preOrder.at(i+1);
            }
            _preOrder.at(_preOrder.size() - 1)->_next = nullptr;
            return OrgChartIterator{_root};
        }

        OrgChartIterator end_preorder(){
            return nullptr;
        }

        OrgChartIterator begin(){
            this->BFS();
            return OrgChartIterator{_root};
        }
        OrgChartIterator end(){
            return nullptr;
        }

    };
}

