using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Calculator.Core.Contracts
{
    public interface ISubscriptionRequest
    {
        string Name { get; set; }
        string Url { get; set; }
        Guid Token { get; set; }
        DateTime ExpireOn { get; set; }
    }
}
