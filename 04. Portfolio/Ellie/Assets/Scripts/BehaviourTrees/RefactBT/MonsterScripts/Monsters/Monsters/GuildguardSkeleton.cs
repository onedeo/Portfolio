using System.Collections;
using Assets.Scripts.Managers;

namespace Scripts.BehaviourTrees.Monster
{
    public class GuildguardSkeleton : MonsterBase
    {
        private enum ParsingData
        {
            MonsterStat = 1903,
            MeleeAttack = 2002,
            RunToPlayer = 2007,
            WeaponAttack = 2101,
        }

        private MeleeAttackData meleeAttackData;
        private RunToPlayerData runData;
        private WeaponAttackData weaponAttackData;

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
            weaponAttackData = DataManager.Instance.GetIndexData<WeaponAttackData, MonsterAttackDataparsingInfo>((int)ParsingData.WeaponAttack);

            SetSkills();
            SetMonsterData(monsterStat);

            tree.AddMonsterData<MonsterStatData>(MonsterData.MonsterStat, monsterStat);
            tree.AddMonsterData<MeleeAttackData>(MonsterData.Melee, meleeAttackData);
            tree.AddMonsterData<RunToPlayerData>(MonsterData.RunToPlayer, runData);
            tree.AddMonsterData<WeaponAttackData>(MonsterData.Weapon, weaponAttackData);
        }
        private void SetSkills()
        {
            MonsterMeleeAttack meleeAttack = new();
            meleeAttack.SetInitialData(meleeAttackData);
            AddAttack(MonsterSkill.Melee, meleeAttack);

            MonsterWeaponeAttack weaponeAttack = new();
            weaponeAttack.SetInitialData(weaponAttackData);
            AddAttack(MonsterSkill.Weapon, weaponeAttack);
        }
    }
}