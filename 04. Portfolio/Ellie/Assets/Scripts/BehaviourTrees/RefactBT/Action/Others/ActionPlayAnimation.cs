using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Scripts.BehaviourTrees.RefactBT
{
    public class ActionPlayAnimation : Node
    {
        private Animator animator;
        AnimationType animation;
        public ActionPlayAnimation(Transform transform, AnimationType animation)
        {
            if(animator==null)
            {
                animator = transform.GetComponent<Animator>();
                if (animator == null)
                    Debug.Log(transform.name + "Try Play Animation But No Animator");
            }
            this.animation = animation;
        }
        protected override void OnStart()
        {
            animator.SetTrigger(animation.ToString());
        }
    }
}