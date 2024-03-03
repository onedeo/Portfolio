using System.Collections.Generic;
using UnityEngine;

namespace Scripts.BehaviourTrees.Monster
{
    public class MonsterNode : Node
    {
        protected MonsterBehaviourTree tree;

        public MonsterNode() : base()
        {
            tree = baseTree as MonsterBehaviourTree;
            if (tree == null)
                Debug.LogFormat("Tree DownCasting To MonsterBehaviourTree Failed : {0}", transform.name);
            transform = tree.GetComponentData<Transform>(MonsterComponentData.TRANSFORM);
        }
        public MonsterNode(List<Node> children) : base(children) { }

        protected void DebugNull(Transform trns, MonsterComponentData component)
        {
            Debug.LogFormat("{0} Is Trying To Access {1}, Which It Does Not Have : {0} / {1}", trns.name, component.ToString());
        }
    }
}
