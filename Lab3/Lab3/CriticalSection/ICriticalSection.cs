namespace Lab3.CriticalSection
{
    public interface ICriticalSection
    {
        void Enter();
        void Leave();
        bool TryEnter(int timeout);
        void SetSpinCount(uint count);
    }
}