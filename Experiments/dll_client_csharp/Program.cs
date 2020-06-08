using dll_client_csharp;
using System;
using System.Runtime.InteropServices;
using System.Threading;

namespace App
{
    class Program
    {

        // bad shit, better thread using cpp and mutexes for access
        static void SeparateThreadWorker()
        {
            Console.WriteLine("Try opencv (sep thread):");
            DllFromTemplate.tryOpenCv();
        }

        static void Main(string[] args)
        {
            Console.WriteLine("C# Dll Client tester");

            Console.WriteLine($"fromtemplate add(1, 2) -> {DllFromTemplate.add(1, 2)}");

            Console.WriteLine($"emit string by ptr -> {DllFromTemplate.emitStringPtrToString()}");
            Console.WriteLine($"reused string obj -> {DllFromTemplate.emitReusedStringObjPtrToString()}");
            Console.WriteLine($"emit string by ptr (same, but after reused called) -> {DllFromTemplate.emitStringPtrToString()}");
            // -> conclusion = string is copied to CLR however it needs to survive the C stack destruction when returning because CLR processes the string after the extern func call

            var sepThread = new Thread(new ThreadStart(SeparateThreadWorker));
            sepThread.Start();

            Console.WriteLine("End.");
            Console.ReadKey();
        }
    }
}
