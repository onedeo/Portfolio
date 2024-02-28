using UnityEngine;

namespace Scripts.BehaviourTrees.Monster
{
    public class ActionPlayAudio : MonsterNode
    {
        private AudioSource audioSource;
        private MonsterAudioController audioController;
        private MonsterAudioType audioType;
        private bool isLoop;
        private bool isInteruptable;

        public ActionPlayAudio(MonsterAudioType audioType, bool isInteruptable = true, bool isLoop = true) : base()
        {
            if (audioSource == null)
                audioSource = tree.GetComponentData<AudioSource>(MonsterComponentData.AUDIO);
            if (audioSource == null)
                DebugNull(transform, MonsterComponentData.AUDIO);

            if (audioController == null)
                audioController = tree.GetComponentData<MonsterAudioController>(MonsterComponentData.AUDIO_CON);
            if (audioController == null)
                DebugNull(transform, MonsterComponentData.AUDIO_CON);

            this.audioType = audioType;
            this.isLoop = isLoop;
            this.isInteruptable = isInteruptable;
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