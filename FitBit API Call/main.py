from gather_keys_oauth2 import OAuth2Server
import fitbit
import pprint

client_id = '22CVLX'
client_secret = '9e3963473fd942e4c06cb3b7a4cbc2e2'

def main():
    server = OAuth2Server(client_id, client_secret)
    server.browser_authorize()

    profile = server.fitbit.user_profile_get()
    # print('You are authorized to access data for the user: {}'.format(
    #     profile['user']['fullName']))

    # print('TOKEN\n=====\n')
    # for key, value in server.fitbit.client.session.token.items():
    #     print('{} = {}'.format(key, value))

    refresh_token = server.fitbit.client.session.token['refresh_token']
    access_token = server.fitbit.client.session.token['access_token']
    expires_at = server.fitbit.client.session.token['expires_at']

    user = fitbit.Fitbit(client_id, client_secret, access_token, refresh_token, expires_at, server.getRedirect())

    current_steps = user.activities()['summary']['steps']
    goal_steps = user.activities_daily_goal()['goals']['steps']

    distance = goal_steps - current_steps
    if(distance <= 0):
        distance = -1


    distance = distance /2263  #average number of steps in a mile 

    print distance

    return distance

if __name__ == '__main__':
    main()