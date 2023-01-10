#include "graphedge.h"
#include "graphnode.h"

#include <iostream>

GraphNode::GraphNode(int id)
{
    _id = id;
}

GraphNode::~GraphNode()
{
    _childEdges.clear();
}

void GraphNode::AddToken(std::string token)
{
    _answers.push_back(token);
}

void GraphNode::AddEdgeToParentNode(GraphEdge *edge)
{
    _parentEdges.push_back(edge);
}

void GraphNode::AddEdgeToChildNode(std::unique_ptr<GraphEdge> edge)
{
    _childEdges.push_back(std::move(edge));
}


// Udacity Review: GraphNode shall have the signature ChatBot instead of ChatBot&&
// Reason: with ChatBot&& the function would be responsible to move the object. This is not the case with ChatBot&&.
// Instead the move constructor shall be called. The constructor is just called, if the ChatBot object is moved 
// when passing the ChatBot Object with std::move and moving it inside the MoveChatbotHere function.
void GraphNode::MoveChatbotHere(ChatBot chatbot)
{
    std::cout << "expect move assignment operator" << std::endl;
    _chatBot = std::move(chatbot);
    _chatBot.SetCurrentNode(this);
}

void GraphNode::MoveChatbotToNewNode(GraphNode *newNode)
{
    std::cout << "expect move constructor" << std::endl;
    newNode->MoveChatbotHere(std::move(_chatBot));
}

GraphEdge *GraphNode::GetChildEdgeAtIndex(int index)
{
    return _childEdges[index].get();
}