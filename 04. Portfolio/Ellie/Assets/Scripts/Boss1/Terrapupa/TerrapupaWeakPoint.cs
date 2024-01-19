using Assets.Scripts.Combat;
using System;
using UnityEngine;

namespace Boss.Terrapupa
{
    public class TerrapupaWeakPoint : MonoBehaviour, ICombatant
    {
        private Action<IBaseEventPayload> collisionAction;

        public void SubscribeCollisionAction(Action<IBaseEventPayload> action)
        {
            collisionAction -= action;
            collisionAction += action;
        }

        public void Attack(IBaseEventPayload payload)
        {
            
        }

        public void ReceiveDamage(IBaseEventPayload payload)
        {
            // �÷��̾� �Ѿ� -> Combat Channel -> TerrapupaWeakPoint :: ReceiveDamage() -> TerrapupaController
            Debug.Log($"{name} ReceiveDamage :: ���� �浹");
            collisionAction?.Invoke(payload);
        }
    }
}