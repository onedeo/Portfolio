using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Scripts.BehaviourTrees.RefactBT
{
    public class ActionPlayAnimation : MonsterNode
    {
        private AnimationType animation;
        private bool waitToEnd;
        private float animationLength;
        private float accumTime;        

        public ActionPlayAnimation(AnimationType animation, bool waitToEnd=false)
        {
            if (animator == null)
                animator = tree.GetData<Animator>(MonsterData.ANIMATOR);
            if (animator == null)
            {
                string name = tree.GetData<Transform>(MonsterData.TRANSFORM).name;
                Debug.Log("Try To Access Animator That Does Not Have : " + name);

                return;
            }
            this.animation = animation;
            this.waitToEnd = waitToEnd;
        }

        protected override void OnStart()
        {
            animator.SetTrigger(animation.ToString());

            if (waitToEnd)
            {
                accumTime = 0;
                AnimatorClipInfo[] clipInfo = animator.GetCurrentAnimatorClipInfo(0);
                animationLength = clipInfo[0].clip.length;
            }
        }

        public override NodeState Evaluate()
        {            
            if(waitToEnd)
            {
                if (accumTime <= animationLength)
                {
                    accumTime += Time.deltaTime;
                    return NodeState.RUNNING;
                }
                else return NodeState.SUCCESS;
            }

            return NodeState.SUCCESS;
            
        }
    }
}