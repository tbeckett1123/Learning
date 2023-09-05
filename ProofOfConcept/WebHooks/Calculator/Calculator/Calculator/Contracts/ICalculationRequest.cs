using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Calculator.Core.Contracts
{
    public interface ICalculationRequest
    {
        Guid Key { get; set; }
        int OperandOne { get; set; }
        int OperandTwo { get; set; }
        Operations Operation { get; set; }
        Guid Token { get; set; }
        bool Completed { get; set; }
    }
}
