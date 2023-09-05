using Calculator.Core.Contracts;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Calculator.DataService.Contracts
{
    public interface IDataService
    {        
        IEnumerable<ISubscriptionRequest> GetSubscriptions();
        ISubscriptionRequest PutSubscription(ISubscriptionRequest request);
        void DeleteCalculationRequest(Guid key);
        IEnumerable<ICalculationRequest>GetCalculationRequests();
        void PostCalculationRequest(ICalculationRequest request);
    }
}
