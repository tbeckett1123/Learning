using Calculator.Core.Contracts;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Calculator.Core.Models
{
    public class CalculationRequest : ICalculationRequest
    {
        public Guid Key { get; set; }
        public int OperandOne { get; set; }
        public int OperandTwo { get; set; }
        public Operations Operation { get; set; }
        public Guid Token { get; set; }
        public bool Completed { get; set; }
    }
}
