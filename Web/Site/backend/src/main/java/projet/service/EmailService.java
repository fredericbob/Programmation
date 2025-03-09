package projet.service;

import org.springframework.beans.factory.annotation.Value;
import org.springframework.stereotype.Service;
import com.sendgrid.SendGrid;

import com.sendgrid.helpers.mail.objects.Content;
import com.sendgrid.helpers.mail.objects.Email;
import com.sendgrid.Request;
import com.sendgrid.Response;
import com.sendgrid.Method;

import java.io.IOException;

import com.sendgrid.helpers.mail.Mail;

@Service
public class EmailService {

    @Value("${spring.sendgrid.api-key}")
    private String apiKey;

    public void sendValidationEmail(String toEmail, String validationLink) {
        Email from = new Email("lalafrederic05@gmail.com"); // Adresse de l'expéditeur
        Email to = new Email(toEmail);
        Content content = new Content("text/html",
                "<p>Click <a href=\"" + validationLink + "\">here</a> to validate your account.</p>");
        Mail mail = new Mail(from, "rakotonirinafrederic92@gmail.com", to, content);

        SendGrid sg = new SendGrid(apiKey);
        Request request = new Request();
        try {
            request.setMethod(Method.POST);
            request.setEndpoint("mail/send");
            request.setBody(mail.build());
            Response response = sg.api(request);
            System.out.println(response.getStatusCode());
            System.out.println(response.getBody());
            System.out.println(response.getHeaders());
        } catch (IOException ex) {
            System.out.println("Error sending email: " + ex.getMessage());
        }
    }
}
