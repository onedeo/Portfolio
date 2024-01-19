using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Scripts.BehaviourTrees.RefactBT
{
    public class WaitDetection : Tree
    {
        protected override Node SetupTree()
        {
            Node root = new Sequence(new List<Node>)
            {

            }
            
        }
    }

}