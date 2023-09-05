using Calculator.Core.Contracts;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Calculator.Core.Models
{
    public class SubscriptionRequest : ISubscriptionRequest
    {
        public string Name { get; set; }
        public string Url { get; set; }
        public Guid Token { get; set; }
        public DateTime ExpireOn { get; set; }
    }
}
