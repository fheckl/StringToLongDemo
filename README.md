# StringToLongDemo
A simple demo to demonstrate pitfalls in data conversion

## How it all started
At my client there are several stages in the software deployment process (Development, Quality, Rollout and Productive). Recently we deployed a new version to the Rollout system and switched a specific server to run on that system rather than on the production system to try the new features and test for any remaining bugs.

The server reads some of its configuration from a database table (different databases or at least different values each system are possible). One of those values is timeout value in seconds that determines how often the server performs a certain action.

When I looked at that value for this server in the rollout environment I became immediately suspicious. In production that certain action was scheduled to run every 4 seconds, but for the rollout environment that value was set to 31536000000 which amounts to about one thousand years. I thought: "Oh wow, this probably never ran since we switched the server to run in the rollout environment".
But my colleague confirmed that the data the server was meant to produce were there anyway.

## So what happened?
I took a closer look at the code and saw that we used a default value of 60 seconds for that timeout if parsing of the database string value resulted in the numerical value 0.

So I ended up with the little demo code here which told me that Microsoft's C++ parser either is doing some bogus action in certain error cases or even does nothing at all which left us in the happy state that our server did its work but may leave someone else with unexpected and probably undesirable results...
