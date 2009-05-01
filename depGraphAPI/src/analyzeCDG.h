/*
 * Copyright (c) 2007-2008 Barton P. Miller
 * 
 * We provide the Paradyn Parallel Performance Tools (below
 * described as "Paradyn") on an AS IS basis, and do not warrant its
 * validity or performance.  We reserve the right to update, modify,
 * or discontinue this software at any time.  We shall have no
 * obligation to supply such updates or modifications or any other
 * form of support to you.
 * 
 * By your use of Paradyn, you understand and agree that we (or any
 * other person or entity with proprietary rights in Paradyn) are
 * under no obligation to provide either maintenance services,
 * update services, notices of latent defects, or correction of
 * defects for Paradyn.
 * 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#if !defined(CDG_ANALYZER_H)
#define CDG_ANALYZER_H

#include <map>
#include <set>

#include "Node.h"
#include "Graph.h"
#include "DepGraphNode.h"
#include "CDG.h"

class BPatch_basicBlock;
class BPatch_flowGraph;
class BPatch_function;

using namespace std;

namespace Dyninst {
namespace DepGraphAPI {


/**
 * The tool that creates the Control Dependence Graph (CDG) associated with a given 
 * function (currently BPatch_function). It uses Dominator Analysis provided by
 * Dyninst. The algorithm is borrowed from Ferrante et. al.
 */
class CDGAnalyzer {

    typedef BPatch_function Function;

 public:
  
  // TODO: replace this with ParsingAPI concepts.
  // Right now we use BPatch_basicBlock since it has
  // dominator info
  typedef BPatch_basicBlock Block;
  
  typedef std::set<Block *> BlockSet;

  typedef map<Block *, BlockSet> BlockMap;

  typedef Node::Ptr NodePtr;

  typedef map<Block *, NodePtr> NodeMap;

 private:
  // Temporary structure to hold nodes we've already
  // created
  NodeMap nodeMap;

  /**
   * Control Dependence Graph.
   */
  CDG::Ptr cdg;

  /*
   * Function 
   */
  Function *func_;

  void createDependencies(BlockSet &blocks);

  Node::Ptr makeNode(Block *);
  
public:
  CDGAnalyzer(Function *f);
  
  CDG::Ptr analyze();

};

};
};
#endif /* INTRACDGCREATOR_H_ */
