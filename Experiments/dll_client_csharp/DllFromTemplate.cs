using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace dll_client_csharp
{
    class DllFromTemplate
    {
        const string dllname = "dll00_fromtemplate.dll";

        [DllImport(dllname)]
        public static extern int add(int a, int b);

        // get string using global std::string in dll
        [DllImport(dllname)]
        public static extern IntPtr emitStringPtr();
        public static string emitStringPtrToString()
        {
            return Marshal.PtrToStringAnsi(emitStringPtr());
        }

        // reuse the object
        [DllImport(dllname)]
        public static extern IntPtr emitReusedStringObjPtr();
        public static string emitReusedStringObjPtrToString()
        {
            return Marshal.PtrToStringAnsi(emitReusedStringObjPtr());
        }
        
        // doesnt work bad practice needs setup on cpp
        [DllImport(dllname)]
        [return: MarshalAs(UnmanagedType.LPWStr)]
        public static extern string emitStringAutoMarshal();

        [DllImport(dllname)]
        public static extern void tryOpenCv();
    }
}
