
using ctci.Contracts;
using Chapter01;
using Chapter02;
using Chapter03;
using Chapter04;
using Chapter05;
using Chapter07;
using Chapter09;
using Chapter11;
using Chapter17;
using Chapter18;
using Introduction;
using System;

namespace ctci
{
    class Program
    {
        static void Main(string[] args)
        {
            IQuestion[] questions = 
            {
                // Intro
                new CompareBinaryToHex(), new SwapMinMax(), 

                // Chapters
                new Q01_1(),                    new Q01_2(), new Q01_3(), new Q01_4(), new Q01_5(), new Q01_6(), new Q01_7(), new Q01_8(),
                new Q02_1(),                    new Q02_2(), new Q02_3(), new Q02_4(), new Q02_5(), new Q02_6(), new Q02_7(), new Q02_Bonus1(), 
                new Q03_1_A(), new Q03_1_B(),   new Q03_2(), new Q03_3(), new Q03_4(), new Q03_5(), new Q03_6(), new Q03_7(),
                new Q04_1(),                    new Q04_2(), new Q04_3(), new Q04_4(), new Q04_5(), new Q04_6(), new Q04_7(), new Q04_8(), new Q04_9(),
                                                new Q05_1(), new Q05_2(), new Q05_3(), new Q05_5(), new Q05_6(), new Q05_7(), new Q05_8(), 
                                                                          new Q07_3(), new Q07_4(), new Q07_5(), new Q07_6(), new Q07_7(), 
                                                                                                    new Q09_6(),
                new Q11_1(),                    new Q11_2(),
                                                             new Q17_3(), new Q17_4(),                                                                                new Q17_11(), new Q17_12(),
                new Q18_1(),                    new Q18_2(),                                                                               new Q18_9(), new Q18_10(), new Q18_11()
            };

            foreach (IQuestion q in questions)
            {
                Console.WriteLine(string.Format("{0}{1}", Environment.NewLine, Environment.NewLine));
                Console.WriteLine(string.Format("// Executing: {0}", q.GetType().ToString()));
                Console.WriteLine("// ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----");

                q.Run();
            }

            Console.WriteLine(string.Format("{0}{1}", Environment.NewLine, Environment.NewLine));
            Console.WriteLine("Press [Enter] to quit");
            Console.ReadLine();
        }
    }
}