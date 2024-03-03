using UnityEngine;

namespace Scripts.BehaviourTrees.Monster
{
    public class ActionExecuteAttack : MonsterNode
    {
        MonsterSkill monsterSkill;
        MonsterBase monster;

        public ActionExecuteAttack(MonsterSkill monsterSkill)
        {
            if(monster==null)
            monster = tree.GetComponentData<MonsterBase>(MonsterComponentData.MONSTER);
            if (monster == null)
                DebugNull(transform, MonsterComponentData.MONSTER);

            this.monsterSkill = monsterSkill;
        }
        public override NodeState Evaluate()
        {
            if (monster.ExecuteAttack(monsterSkill))
                return NodeState.SUCCESS;

            Debug.LogFormat("{0} Is Trying To Attack With {1} That Does Not have : {0}, {1}", transform.name, monsterSkill.ToString());
            return NodeState.FAILURE;
        }
    }
}
