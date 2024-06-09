#include "services/booru/GelbooruProvider.hpp"
#include "services/booru/SafebooruProvider.hpp"

QNetworkRequest SafebooruProvider::prepareRequest(const BooruSearchParameters& parameters)
{
        return PrepareGelbooruRequest("safebooru.org", parameters);
}

std::variant<QList<BooruImage*>, QString> SafebooruProvider::tryParseReply(QNetworkReply& reply) const
{
	QDomDocument xmlResponse;
	if(QDomDocument::ParseResult parseResult = xmlResponse.setContent(&reply); !parseResult)
	{
		//TODO: error message
		return "";
	}

	QDomElement postsNode = xmlResponse.firstChildElement("posts");
	if(postsNode.isNull())
	{
		return "Parsing error: root element \"posts\" was not found.";
	}

	QList<BooruImage*> result;

	QDomElement postNode = postsNode.firstChildElement("post");

	for(; !postNode.isNull(); postNode = postNode.nextSiblingElement("post"))
	{
		QString fileUrl    = postNode.attribute("file_url", "");
		QString previewUrl = postNode.attribute("preview_url", "");

		if(fileUrl.isEmpty() || previewUrl.isEmpty())
		{
			qDebug() << "Parsing error: could not find file_url or preview_url; skipping image.";
			continue;
		}

		result.append(new BooruImage(QUrl(previewUrl), QUrl(fileUrl)));
	}

	return result;
}