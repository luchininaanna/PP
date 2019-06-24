using System;
using System.Threading;

namespace Lab3.CriticalSection
{
    public class CriticalSection : ICriticalSection
    {
        private static Mutex Mut { get; } = new Mutex();
        private static uint _spinCount;

        public CriticalSection(uint count)
        {
            SetSpinCount(count);
        }
        
        public void Enter()
        {
            var attemptNumber = 0;
            if (Mut.WaitOne(0, false))
                return;

            while (!Mut.WaitOne(0, false))
            {
                attemptNumber++;

                if (attemptNumber != _spinCount)
                    continue;

                attemptNumber = 0;
                Thread.Sleep(10);
            }
        }

        public bool TryEnter(int timeout)
        {
            var attemptNumber = 0;
            var startTime = DateTime.Now.Millisecond;
            if (Mut.WaitOne(0, false))
                return true;

            while (!Mut.WaitOne(0, false))
            {
                attemptNumber++;

                if (DateTime.Now.Millisecond >= startTime + timeout)
                    return false;

                if (attemptNumber != _spinCount)
                    continue;

                attemptNumber = 0;
                Thread.Sleep(10);
            }
       
            return true;
        }

        public void SetSpinCount(uint count)
        {
            _spinCount = count;
        }

        public void Leave()
        {
            Mut.ReleaseMutex();
        }
    }
}