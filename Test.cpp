#include "doctest.h"
#include "sources/OrgChart.hpp"
using namespace ariel;

#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

TEST_CASE("add root || add sub"){
    OrgChart organization;
    CHECK_NOTHROW(organization.add_root("CEO"));
    CHECK_THROWS(organization.add_sub("Roi", "Naor")); // "Roi" doesn't exist in the OrgChart
    CHECK_NOTHROW(organization.add_root("Roi")); // replace the root from "CEO" to "Roi"
    CHECK_NOTHROW(organization.add_sub("Roi","Daniel"));
    CHECK_NOTHROW(organization.add_sub("Daniel","Ofir"));

}
TEST_CASE("Iterators"){
    OrgChart organization;
    organization.add_root("CEO")
            .add_sub("CEO", "CTO")         // Now the CTO is subordinate to the CEO
            .add_sub("CEO", "CFO")         // Now the CFO is subordinate to the CEO
            .add_sub("CEO", "COO")         // Now the COO is subordinate to the CEO
            .add_sub("CTO", "VP_SW") // Now the VP Software is subordinate to the CTO
            .add_sub("COO", "VP_BI");      // Now the VP_BI is subordinate to the COO
    vector<string> levelOrderAns={"CEO","CTO","CFO","COO","VP_SW","VP_BI"};
    unsigned int i =0;
    for (auto it = organization.begin_level_order(); it != organization.end_level_order(); ++it){
        OrgChart::Node* curr = (&it);
        CHECK(curr->_value == levelOrderAns.at(i++));

    }
    vector<string> revOrderAns={"VP_SW","VP_BI","CTO","CFO","COO","CEO"};
    i=0;
    for (auto it=organization.begin_reverse_order(); it!=organization.reverse_order(); ++it) {
        OrgChart::Node* curr = (&it);
        CHECK(curr->_value == revOrderAns.at(i++));
    }
    vector<string> preOrderOrder={"CEO","CTO","VP_SW","CFO","COO","VP_BI"};
    i=0;
    for (auto it=organization.begin_preorder(); it!=organization.end_preorder(); ++it) {
        OrgChart::Node* curr = (&it);
        CHECK(curr->_value == preOrderOrder.at(i++));
    }

}

TEST_CASE("draft"){
    OrgChart organization;
    organization.add_root("CEO")
            .add_sub("CEO", "CTO")         // Now the CTO is subordinate to the CEO
            .add_sub("CEO", "CFO")         // Now the CFO is subordinate to the CEO
            .add_sub("CEO", "COO")         // Now the COO is subordinate to the CEO
            .add_sub("CTO", "VP_SW") // Now the VP Software is subordinate to the CTO
            .add_sub("COO", "VP_BI");      // Now the VP_BI is subordinate to the COO

    for (auto it = organization.begin_level_order(); it != organization.end_level_order(); ++it)
    {
        cout << (*it) << " " ;
    }
    cout <<""<< endl;

    for (auto it = organization.begin_reverse_order(); it != organization.reverse_order(); ++it)
    {
        cout << (*it) << " " ;
    } // prints: VP_SW VP_BI CTO CFO COO CEO
    cout <<""<< endl;
    for (auto it=organization.begin_preorder(); it!=organization.end_preorder(); ++it) {
        cout << (*it) << " " ;
    }  // prints: CEO CTO VP_SW CFO COO VP_BI
    cout <<""<< endl;
}