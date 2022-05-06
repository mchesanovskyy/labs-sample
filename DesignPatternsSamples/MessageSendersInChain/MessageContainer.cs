using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading;
using MessageSendersInChain.Senders;

namespace MessageSendersInChain
{
    public class MessageContainer
    {
        public IMessageSender CreateMessageSender(string[] types)
        {
            var senders = GetSenders(types);
            return BuildSendersInChain(senders);
        }

        /// <summary>
        /// Defines the sequence of IMessageSender's instances
        /// The first instance of the list will be invoked first
        /// </summary>
        private static ICollection<MessageSenderBase> GetSenders(string[] types)
        {
            var senders = new List<MessageSenderBase>();
            senders.Add(new ValidateNullMessage());
            senders.Add(new ValidateMessageLength());

            var typesWithoutDuplicates = types.Distinct(StringComparer.OrdinalIgnoreCase);
            foreach (var type in typesWithoutDuplicates)
            {
                switch (type.ToUpper())
                {
                    case "SMS": senders.Add(new SmsMessageSender()); break;
                    case "EMAIL": senders.Add(new EmailMessageSender()); break;
                }
            }
            return senders;
        }

        /// <summary>
        /// In order to build senders in one chain we should link ever sender with next sender.
        /// senders[i] (outer, parent) link to senders[i + 1] (inner, next)
        /// </summary>
        /// <returns></returns>
        private static IMessageSender BuildSendersInChain(ICollection<MessageSenderBase> senders)
        {
            if (senders == null || !senders.Any())
            {
                // if senders is null or empty
                return null;
            }

            var previousSender = senders.First();
            foreach (var sender in senders)
            {
                previousSender.SetNext(sender);
                previousSender = sender;
            }

            return senders.First();
        }
    }
}