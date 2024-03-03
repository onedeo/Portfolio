using System.Collections;
using Assets.Scripts.Managers;

namespace Scripts.BehaviourTrees.Monster
{
    public class NormalSkeleton : MonsterBase
    {
        private enum ParsingData
        {
            MonsterStat = 1900,
            MeleeAttack = 2000,
            RunToPlayer = 2005,
        }

        private MeleeAttackData meleeAttackData;
        private RunToPlayerData runData;

        protected override void Start()
        {
            base.Start();
            StartCoroutine(InitParsingData());
        }
        private IEnumerator InitParsingData()
        {
            yield return DataManager.Instance.CheckIsParseDone();

            monsterStat = DataManager.Instance.GetIndexData<MonsterStatData, MonsterStatDataParsingInfo>((int)ParsingData.MonsterStat);
            meleeAttackData = DataManager.Instance.GetIndexData<MeleeAttackData, MonsterAttackDataparsingInfo>((int)ParsingData.MeleeAttack);
            runData = DataManager.Instance.GetIndexData<RunToPlayerData, MonsterAttackDataparsingInfo>((int)ParsingData.RunToPlayer);

            SetSkills();
            SetMonsterData(monsterStat);

            tree.AddMonsterData<MonsterStatData>(MonsterData.MonsterStat, monsterStat);
            tree.AddMonsterData<MeleeAttackData>(MonsterData.Melee, meleeAttackData);
            tree.AddMonsterData<RunToPlayerData>(MonsterData.RunToPlayer, runData);
            
        }
        private void SetSkills()
        {
            MonsterMeleeAttack meleeAttack = new();
            meleeAttack.SetInitialData(meleeAttackData);
            AddAttack(MonsterSkill.Melee, meleeAttack);
        }
    }
}