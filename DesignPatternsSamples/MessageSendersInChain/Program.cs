namespace MessageSendersInChain
{
    class Program
    {
        static void Main(string[] args)
        {
            var container = new MessageContainer();

            var messageTypes = new[] { "Email", "SMS"};
            // Chain will include: ValidateNullMessage, ValidateMessageLength
            // + EmailMessageSender, SmsMessageSender on demand (based on messageTypes)
            var sender = container.CreateMessageSender(messageTypes);

            var message = "Test messageTest message";
            sender.Send(message);
        }
    }
}
