using System;

namespace MessageSendersInChain.Senders
{
    public class SmsMessageSender : MessageSenderBase
    {
        public SmsMessageSender() { }

        public override void Send(string message)
        {
            Console.WriteLine($"Send SMS with {message}");
            base.Send(message);
        }
    }
}