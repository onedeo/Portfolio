using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Scripts.BehaviourTrees.RefactBT
{
    public class ActionPlayAudio : MonsterNode
    {
        private MonsterAudioType audioType;
        private bool isLoop;
        private bool isInteruptable;
        public ActionPlayAudio(MonsterAudioType audioType, bool isInteruptable = true, bool isLoop = true) : base()
        {
            if (audioSource == null)
                audioSource = transform.GetComponent<AudioSource>();
            if(audioSource==null)
            {
                string name = tree.GetData<Transform>(MonsterData.TRANSFORM).name;
                Debug.Log("Try To Access AudioSource That Does Not Have : " + name);
            }

            if (audioController == null)
                audioController = transform.GetComponent<MonsterAudioController>();
            if(audioController==null)
            {
                string name = tree.GetData<Transform>(MonsterData.TRANSFORM).name;
                Debug.Log("Try To Access AudioController That Does Not Have : " + name);
            }

            this.audioType = audioType;
            this.isLoop = isLoop;
            this.isInteruptable = isInteruptable;
        }

        protected override void OnStart()
        {
            
        }

        public override NodeState Evaluate()
        {
            if (isLoop)
                audioSource.loop = true;
            else audioSource.loop = false;

            if (!isInteruptable)
            {
                if (audioSource.isPlaying)
                    return NodeState.SUCCESS;
            }

            AudioClip clip = audioController.GetAudio(audioType);
            if(clip==null)
            {
                Debug.Log(transform.name + "Try To Play Audio Does Not Have: " + audioType.ToString());
                return NodeState.FAILURE;
            }
            audioSource.clip = clip;
            audioSource.Play();

            return NodeState.SUCCESS;
        }

    }
}