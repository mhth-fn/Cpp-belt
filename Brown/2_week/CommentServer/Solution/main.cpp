

HttpResponse CommentServer::ServeRequest(const HttpRequest& req) {
    if (req.method == "POST") {
      if (req.path == "/add_user") {
        comments_.emplace_back();
        auto response = to_string(comments_.size() - 1);
        return HttpResponse(HttpCode::Ok).SetContent(response);
      } else if (req.path == "/add_comment") {
        auto [user_id, comment] = ParseIdAndContent(req.body);

        if (!last_comment || last_comment->user_id != user_id) {
          last_comment = LastCommentInfo{user_id, 1};
        } else if (++last_comment->consecutive_count > 3) {
          banned_users.insert(user_id);
        }

        if (banned_users.count(user_id) == 0) {
          comments_[user_id].push_back(string(comment));
          return HttpResponse(HttpCode::Ok);
          //os << "HTTP/1.1 200 OK\n\n";
        } else {
          return HttpResponse(HttpCode::Found).AddHeader("Location", "/captcha");
          //os << "HTTP/1.1 302 Found\n\n"
          //  "Location: /captcha\n"
          //  "\n";
        }
      } else if (req.path == "/checkcaptcha") {
        if (auto [id, response] = ParseIdAndContent(req.body); response == "42") {
          banned_users.erase(id);
          if (last_comment && last_comment->user_id == id) {
            last_comment.reset();
          }
          return HttpResponse(HttpCode::Ok);
          //os << "HTTP/1.1 200 OK\n\n";
        } else {
          return HttpResponse(HttpCode::Found).AddHeader("Location", "/captcha");
        }
      }
        //os << "HTTP/1.1 404 Not found\n\n";
    } else if (req.method == "GET") {
      if (req.path == "/user_comments") {
        auto user_id = FromString<size_t>(req.get_params.at("user_id"));
        string response;
        for (const string& c : comments_[user_id]) {
          response += c + '\n';
        }
        return HttpResponse(HttpCode::Ok).SetContent(response);
        //os << "HTTP/1.1 200 OK\n" << "Content-Length: " << response.size() << response;
      } else if (req.path == "/captcha") {
        return HttpResponse(HttpCode::Ok).SetContent("What's the answer for The Ultimate Question of Life, the Universe, and Everything?");
        //os << "HTTP/1.1 200 OK\n" << "Content-Length: 80\n" << "\n"
        //  << "What's the answer for The Ultimate Question of Life, the Universe, and Everything?";
      } else {
        return HttpResponse(HttpCode::NotFound);
        //os << "HTTP/1.1 404 Not found\n\n";
      }
    }
    return HttpResponse(HttpCode::NotFound);
  }