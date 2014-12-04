public static JSONObject getJSONFromUrl(String url, HashMap<String, String> map) {
		InputStream is = null;
		HttpResponse response;
		HttpClient httpclient = new DefaultHttpClient();
	    HttpPost httppost = new HttpPost(url);
	    String json = "";
		JSONObject jObj = null;

	    if (map != null) {
	    	try {
	    		List<NameValuePair> list = new ArrayList<NameValuePair>();
	    		for (HashMap.Entry<String, String> entry : map.entrySet()) {
	    			list.add(new BasicNameValuePair(entry.getKey(), entry.getValue()));
	    		}
				httppost.setEntity(new UrlEncodedFormEntity(list));
			} catch (UnsupportedEncodingException e) {
				e.printStackTrace();
			}
	    }

		try {
			response = httpclient.execute(httppost);
			HttpEntity httpEntity = response.getEntity();
			is = httpEntity.getContent();
		} catch (ClientProtocolException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}

		try {
			BufferedReader reader = new BufferedReader(new InputStreamReader(is, "utf-8"), 8);
			StringBuilder sb = new StringBuilder();
			String line = null;
			while ((line = reader.readLine()) != null) {
				sb.append(line + "n");
			}
			is.close();
			json = sb.toString();
		} catch (Exception e) {
			Log.i(TAG, "Error converting result " + e.toString());
		}

		try {
			jObj = new JSONObject(json);
		} catch (JSONException e) {
			e.printStackTrace();
		}
		return jObj;
	}
