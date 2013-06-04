import java.io.IOException;
import java.net.HttpURLConnection;
import java.net.URL;

public static boolean ping(String url, int timeout) {
    // Otherwise an exception may be thrown on invalid SSL certificates.
    url = url.replaceFirst("https", "http");
    HttpURLConnection connection = null;
    try {
        connection = (HttpURLConnection) new URL(url).openConnection();
        connection.setConnectTimeout(timeout);
        connection.setReadTimeout(timeout);
        connection.setRequestMethod("HEAD");
        int responseCode = connection.getResponseCode();
        return (200 <= responseCode && responseCode <= 399);
    } catch (IOException exception) {
        return false;
    } finally {
        if (connection != null) {
            connection.disconnect();
        }
    }
}

