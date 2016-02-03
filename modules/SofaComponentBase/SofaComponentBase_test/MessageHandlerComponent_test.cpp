/******************************************************************************
*       SOFA, Simulation Open-Framework Architecture, development version     *
*                (c) 2006-2015 INRIA, USTL, UJF, CNRS, MGH                    *
*                                                                             *
* This library is free software; you can redistribute it and/or modify it     *
* under the terms of the GNU Lesser General Public License as published by    *
* the Free Software Foundation; either version 2.1 of the License, or (at     *
* your option) any later version.                                             *
*                                                                             *
* This library is distributed in the hope that it will be useful, but WITHOUT *
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or       *
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License *
* for more details.                                                           *
*                                                                             *
* You should have received a copy of the GNU Lesser General Public License    *
* along with this library; if not, write to the Free Software Foundation,     *
* Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA.          *
*******************************************************************************
*                               SOFA :: Modules                               *
*                                                                             *
* This component is open-source                                               *
*                                                                             *
* Authors: Damien Marchal                                                     *
*                                                                             *
* Contact information: contact@sofa-framework.org                             *
******************************************************************************/
#include <gtest/gtest.h>

#include <string>
using std::string ;

#include <sofa/simulation/graph/DAGSimulation.h>
using sofa::simulation::graph::DAGSimulation ;

#include <sofa/simulation/common/Simulation.h>
using sofa::simulation::Simulation ;

#include <sofa/simulation/common/Node.h>
using sofa::simulation::Node ;

#include <sofa/simulation/common/SceneLoaderXML.h>
using sofa::simulation::SceneLoaderXML ;

#include <SofaComponentBase/messageHandlerComponent.h>
using sofa::component::logging::MessageHandlerComponent ;

TEST(MessageHandlerComponent, simpleInit)
{
    string scene =
        "<?xml version='1.0'?>                                               "
        "<Node 	name='Root' gravity='0 0 0' time='0' animate='0'   >         "
        "   <Node>  "
            "       <MessageHandlerComponent handler='silent'/>              "
        "   </Node> "
        "</Node>                                                             " ;

    sofa::simulation::setSimulation(new DAGSimulation());

    Node::SPtr root = SceneLoaderXML::loadFromMemory ( "test1",
                                                       scene.c_str(),
                                                       scene.size() ) ;
    EXPECT_TRUE(root!=NULL) ;

    MessageHandlerComponent* component = NULL;

    root->getTreeObject(component) ;
    EXPECT_TRUE(component!=NULL) ;
}


TEST(MessageHandlerComponent, missingHandler)
{
    string scene =
        "<?xml version='1.0'?>                                               "
        "<Node 	name='Root' gravity='0 0 0' time='0' animate='0'   >         "
        "       <MessageHandlerComponent/>                   "
        "</Node>                                                             " ;

    Node::SPtr root = SceneLoaderXML::loadFromMemory ( "test1",
                                                       scene.c_str(),
                                                       scene.size() ) ;

    MessageHandlerComponent* component = NULL;
    root->getTreeObject(component) ;
    EXPECT_TRUE(component!=NULL) ;
    EXPECT_FALSE(component->isValid()) ;
}

TEST(MessageHandlerComponent, invalidHandler)
{
    string scene =
        "<?xml version='1.0'?>                                               "
        "<Node 	name='Root' gravity='0 0 0' time='0' animate='0'   >         "
        "       <MessageHandlerComponent handler='thisisinvalid'/>           "
        "</Node>                                                             " ;

    Node::SPtr root = SceneLoaderXML::loadFromMemory ( "test1",
                                                       scene.c_str(),
                                                       scene.size() ) ;

    MessageHandlerComponent* component = NULL;
    root->getTreeObject(component) ;
    EXPECT_TRUE(component!=NULL) ;
    EXPECT_FALSE(component->isValid()) ;
}

TEST(MessageHandlerComponent, clangHandler)
{
    string scene =
        "<?xml version='1.0'?>                                               "
        "<Node 	name='Root' gravity='0 0 0' time='0' animate='0'   >         "
        "       <MessageHandlerComponent handler='clang'/>                   "
        "</Node>                                                             " ;

    Node::SPtr root = SceneLoaderXML::loadFromMemory ( "test1",
                                                       scene.c_str(),
                                                       scene.size() ) ;

    MessageHandlerComponent* component = NULL;
    root->getTreeObject(component) ;
    EXPECT_TRUE(component!=NULL) ;
    EXPECT_TRUE(component->isValid()) ;
}