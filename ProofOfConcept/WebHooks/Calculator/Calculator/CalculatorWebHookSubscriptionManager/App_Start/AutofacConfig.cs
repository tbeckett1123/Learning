using Autofac;
using Autofac.Integration.Mvc;
using Autofac.Integration.WebApi;
using Calculator.Core.Contracts;
using Calculator.Core.Models;
using Calculator.DataService.Contracts;
using Calculator.DataService.Models;
using CalculatorWebHookSubscriptionManager.BusinessLogic;
using MediatR;
using System.Configuration;
using System.Reflection;
using System.Web.Http;
using System.Web.Mvc;

namespace CalculatorWebHookSubscriptionManager.App_Start
{
    /// <summary>
    /// Autofac configuration and setup tasks
    /// </summary>
    internal static class AutofacConfig
    {
        /// <summary>
        /// Runs tasks to setup autofac
        /// </summary>
        public static void Run()
        {
            var builder = new ContainerBuilder();

            RegisterTypes(builder);
            RegisterDependencyResolver(builder);
        }

        /// <summary>
        /// Set's up the GlobalConfiguration's DependencyResolver.
        /// </summary>
        /// <param name="builder"></param>
        public static void RegisterDependencyResolver(ContainerBuilder builder)
        {
            var container = builder.Build();
            
            DependencyResolver.SetResolver(new AutofacDependencyResolver(container));
            GlobalConfiguration.Configuration.DependencyResolver = new AutofacWebApiDependencyResolver(container);
        }

        /// <summary>
        /// Registers types for the container builder for autofac.
        /// </summary>
        /// <param name="builder"></param>
        public static void RegisterTypes(ContainerBuilder builder)
        {
            builder.RegisterModelBinders(Assembly.GetExecutingAssembly());

            // * The service factor is required to create an instance of mediator
            // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
            builder.RegisterType<Mediator>().As<IMediator>().InstancePerLifetimeScope();
            builder.Register<ServiceFactory>(b =>
            {
                var x = b.Resolve<IComponentContext>();
                return t => x.Resolve(t);
            });

            builder.RegisterType<SubscriptionRequest>().As<ISubscriptionRequest>().InstancePerDependency();
            builder.RegisterType<CalculationRequest>().As<ICalculationRequest>().InstancePerDependency();
            builder.RegisterType<DataService>().As<IDataService>().InstancePerDependency();            
            builder.RegisterType<CalculatorWebHookSubscriptionService>().As<ICalculatorWebHookSubscriptionService>().InstancePerDependency();

            
        }                       
    }
}