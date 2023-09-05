using Calculator.Core.Contracts;
using MediatR;
using System;
using System.Web.Http;
using System.Web.Mvc;

namespace CalculatorWebHookSubscriptionManager.Controllers
{
    public class HomeController : Controller
    {
        private IMediator _Mediator;
        public HomeController(
            IMediator mediator 
            //,ICalculatorWebHookSubscriptionService calculatorWebHookSubscriptionService
        )
        {
            _Mediator = mediator ?? throw new ArgumentNullException("mediator");
            //_CalculatorWebHookSubscriptionService = calculatorWebHookSubscriptionService ?? throw new ArgumentNullException("calculatorWebHookSubscriptionService");
        }

        //private ICalculatorWebHookSubscriptionService _CalculatorWebHookSubscriptionService;

        //public HomeController(ICalculatorWebHookSubscriptionService calculatorWebHookSubscriptionService) => _CalculatorWebHookSubscriptionService = calculatorWebHookSubscriptionService ?? throw new NullReferenceException("calculatorWebHookSubscriptionService");

        public ActionResult Index() => View(DependencyResolver.Current.GetService<ISubscriptionRequest>());

        //[System.Web.Http.HttpPost]
        //public ActionResult Register([FromBody] ISubscriptionRequest request) => View("Index", _CalculatorWebHookSubscriptionService.Subscribe(request));
    }
}