using System;
using System.Collections.Generic;
using System.Threading;
using Lab3.Assets;

namespace Lab3
{
    internal static class Program
    {
        private static double _pi;
        private static int _timeout;
        private const int COUNT_THREADS = 4;
        private static CriticalSection.CriticalSection _criticalSection;
        
        public static void Main(string[] args)
        {
            bool isNeedToContinue = IsCorrectInputData(args);
            if (!isNeedToContinue)
                return;
            
            bool isParamNotInt = !int.TryParse(args[0], out var countSteps);
            if (isParamNotInt)
            {
                Console.WriteLine("Incorrect value <steps>. Value should be a number");
                return;
            }

            isParamNotInt = !int.TryParse(args[1], out _timeout);
            if (isParamNotInt)
            {
                Console.WriteLine("Incorrect value <timeout>. Value should be a number");
                return;
            }

            isParamNotInt = !uint.TryParse(args[2], out var countTry);
            if (isParamNotInt)
            {
                Console.WriteLine("Incorrect value <count try>. Value should be a number");
                return;
            }

            _criticalSection = new CriticalSection.CriticalSection(countTry);

            var watch = System.Diagnostics.Stopwatch.StartNew();
            var handles = CreateThreads(countSteps, TryType.TryEnter);
            foreach (var tr in handles) tr.Join();
            watch.Stop();
            var elapsedMs = watch.ElapsedMilliseconds;
            Console.WriteLine("Number Pi = " + _pi + ", Work time: " + elapsedMs + "ms, Try Type: " + TryType.TryEnter);

            _pi = 0;

            watch = System.Diagnostics.Stopwatch.StartNew();
            handles = CreateThreads(countSteps, TryType.Enter);
            foreach (var tr in handles) tr.Join();
            watch.Stop();
            elapsedMs = watch.ElapsedMilliseconds;
            Console.WriteLine("Number Pi = " + _pi + ", Work time: " + elapsedMs + "ms, Try Type: " + TryType.Enter);
        }

        private static IEnumerable<Thread> CreateThreads(int countSteps, string tryType)
        {
            var waitHandles = new List<Thread>();
            var countStepsPerThread = countSteps / COUNT_THREADS;
            for (var i = 0; i < COUNT_THREADS; i++)
            {
                var newThread = new Thread(CalcPi);
                newThread.Start(new ThreadContext
                {
                    Left = i * countStepsPerThread,
                    Right = (i + 1) * countStepsPerThread,
                    Step = 1.0 / countSteps,
                    Name = $"Thread: {i}",
                    TryType = tryType
                });
                waitHandles.Add(newThread);
            }

            return waitHandles;
        }

        private static void CalcPi(object param)
        {
            var threadContext = (ThreadContext)param;
            for (var i = threadContext.Left; i < threadContext.Right; i++)
            {
                var x = (i + 0.5) * threadContext.Step;

                if (threadContext.TryType == TryType.Enter)
                    _criticalSection.Enter();
                else
                    while (!_criticalSection.TryEnter(_timeout)) { }

                _pi += 4.0 / (1.0 + x * x) * threadContext.Step;
                _criticalSection.Leave();
            }
        }

        private static bool IsCorrectInputData(string[] args)
        {
            bool isNotEnoughtParameters = (args[0] == null && args[1] == null && args[2] == null);
            if (isNotEnoughtParameters)
            {
                Console.WriteLine("Invalid number of arguments. You should enter data in the next view: " +
                    "Lab3.exe <count steps> <timeout> <count try>");
                return false;
            }

            return true;
        }
    }
}