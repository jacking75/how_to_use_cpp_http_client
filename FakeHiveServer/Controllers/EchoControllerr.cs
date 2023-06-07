using Microsoft.AspNetCore.Mvc;


namespace APIServer.Controllers;

[ApiController]
[Route("[controller]")]
public class Echo : ControllerBase
{
    [HttpPost]
    public PkEchoResponse Post(PkEchoRequest request)
    {
        var response = new PkEchoResponse();

        response.BodyData = request.BodyData;

        return response;
    }
}

public class PkEchoRequest
{
    public string BodyData { get; set; }
}

public class PkEchoResponse
{
    public string BodyData { get; set; }
}
